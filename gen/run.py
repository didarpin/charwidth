#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# https://unicode.org/Public
# https://www.unicode.org/reports/tr44
# https://www.unicode.org/reports/tr11
# https://www.unicode.org/reports/tr51
# https://www.unicode.org/faq/private_use.html

import os
import os.path
import sys

from pathlib import Path
from jinja2 import Environment, FileSystemLoader
from urllib.request import urlretrieve

########

cf_dir = Path(__file__).parent.resolve()
work_dir = str(cf_dir.parent)
src_dir = os.path.join(work_dir, "src");
test_dir = os.path.join(work_dir, "test");
templates_dir = os.path.join(work_dir, "gen", "templates");
tmp_dir = os.path.join(work_dir, "tmp");

max_codepoint = 0x10ffff

unicode_data = []
eaw_data = []

########

class CodePoint:
	def __init__(self, codepoint):
		self.codepoint = codepoint
		self.width = 0


def DownloadFile(url, file):
	if not os.path.isfile(file):
		print(f"Downloading {url}\n")
		urlretrieve(url, file)


def ReadFile(file):
	with open(file, "rb") as f:
		data = f.read()
	lines = data.decode("utf-8").split("\n")
	new_lines = []
	for line in lines:
		line = line.strip()
		if not line: continue
		if line.startswith("#"): continue
		new_lines.append(line);
	return new_lines


def SetGeneralWidths(cps):
	fields_first = None
	for line in unicode_data:
		fields = line.strip().split(";")
		if fields[1].endswith("First>"):
			fields_first = fields
			continue
		if fields_first:
			if not fields[1].endswith("Last>"):
				print("SetGeneralWidths error")
				sys.exit(1)
			rg = (int(fields_first[0], 16), int(fields[0], 16))
			fields_first = None
		else:
			rg = ToRange(fields[0])

		for cp in range(rg[0], rg[1] + 1):
			if fields[2] not in ["Cs", "Cc", "Cf", "Zl", "Zp", "Mn", "Mc", "Me"]:
				cps[cp].width = 1


def SetEawWidths(cps):
	for line in eaw_data:
		rg, prop = ParseEawLine(line)
		# A : Ambiguous
		# F : Fullwidth
		# H : Halfwidth,
		# N : Neutral(= Not East Asian)
		# Na: Narrow
		# W : Wide
		if prop in ["H", "Na"]:
			SetRangeWidth(rg, 1, cps)
		elif prop in ["F", "W"]:
			SetRangeWidth(rg, 2, cps)
		elif prop == "A":
			SetRangeWidth(rg, -1, cps)


def SetRangeWidth(rg, width, cps):
	for cp in range(rg[0], rg[1] + 1):
		cps[cp].width = width


def MergeCodepoint(cps):
	cps = sorted(cps, key=lambda cp: cp.codepoint)
	if not cps: return []
	rgs = [[cps[0].codepoint, cps[0].codepoint]]
	for cp in cps[1:]:
		if cp.codepoint == rgs[-1][1] + 1:
			rgs[-1][1] = cp.codepoint
			continue
		rgs.append([cp.codepoint, cp.codepoint])
	return rgs


def ToRange(s):
	fields = [int(val, 16) for val in s.split("..")]
	return (fields[0], fields[0 if len(fields) == 1 else 1])


def ParseEawLine(eaw_line):
	line = eaw_line.split("#", 1)[0]
	fields = line.split(";")
	return (ToRange(fields[0]), fields[1].strip())


def ReadData(unicode_file, eaw_file):
	global unicode_data, eaw_data
	unicode_data = ReadFile(unicode_file)
	eaw_data = ReadFile(eaw_file)


def MakeCodepoints():
	cps = [CodePoint(cp) for cp in range(max_codepoint + 1)]
	SetGeneralWidths(cps)
	SetEawWidths(cps)

	# fixed some special characters
	rgs = [
		(0x1160, 0x11ff),
		(0xd7b0, 0xd7ff)
	]
	for i in range(0, 17):
		cp = 0x10000 * i + 0xfffe
		rgs.append((cp, cp + 1))
	for rg in rgs:
		SetRangeWidth(rg, 0, cps)

	return cps


def Do(version):
	global unicode_data, eaw_data

	os.makedirs(os.path.join(tmp_dir, version), exist_ok=True)
	os.makedirs(os.path.join(src_dir, version), exist_ok=True)

	unicode_data_url = f"https://unicode.org/Public/{version}/ucd/UnicodeData.txt"
	unicode_file = os.path.join(tmp_dir, version, f"UnicodeData.txt")

	eaw_url = f"https://unicode.org/Public/{version}/ucd/EastAsianWidth.txt"
	eaw_file = os.path.join(tmp_dir, version, f"EastAsianWidth.txt")

	DownloadFile(unicode_data_url, unicode_file)
	DownloadFile(eaw_url, eaw_file)

	unicode_data = ReadFile(unicode_file)
	eaw_data = ReadFile(eaw_file)

	cps = MakeCodepoints()

	fields = {
		"version": version,
		"width_0": MergeCodepoint((cp for cp in cps if cp.width == 0)),
		"width_1": MergeCodepoint((cp for cp in cps if cp.width == 1)),
		"width_2": MergeCodepoint((cp for cp in cps if cp.width == 2)),
		"width_ambiguous": MergeCodepoint((cp for cp in cps if cp.width == -1)),
	}

	file_names = ("c90.h", "c99.h", "cpp98.h", "cpp11.h", "cpp17.h")

	env = Environment(loader=FileSystemLoader(templates_dir), trim_blocks=True, lstrip_blocks=True)
	env.filters["VersionV"] = FilterVersionV
	env.filters["VersionI"] = FilterVersionI
	for file_name in file_names:
		output_file = os.path.join(src_dir, version, file_name)
		t = env.get_template(f"{file_name}.j2")
		with open(output_file, "w") as f:
			f.write(t.render(fields))

	for v in ["0", "1", "2", "ambiguous"]:
		data = b""
		for n0, n1 in fields[f"width_{v}"]:
			data += n0.to_bytes(4, byteorder='little')
			if n0 != n1: data += n1.to_bytes(4, byteorder='little')

		output_file = os.path.join(test_dir, "data", f"{version}_{v}.dat")
		with open(output_file, "wb") as f:
			f.write(data)


def FilterVersionV(version):
	return version.replace(".", "_")


def FilterVersionI(version):
	v = version.split(".")
	for i in range(len(v)):
		if (i > 0) and (len(v[i]) == 1): v[i] = f"0{v[i]}"
	return "".join(v)


if __name__ == "__main__":
	versions = (
		"7.0.0", "8.0.0", "9.0.0", "10.0.0",
		"11.0.0", "12.0.0", "13.0.0", "14.0.0",
		"15.0.0", "15.1.0", "16.0.0", "17.0.0"
	)
	for version in versions:
		Do(version)

	fields = {
		"versions": versions
	}

	file_names = (
		"def.h", "type_c90.h", "type_c99.h",
		"charwidth_c90.h", "charwidth_c99.h",
		"charwidth_cpp98.h", "charwidth_cpp11.h", "charwidth_cpp17.h",
	)

	env = Environment(loader=FileSystemLoader(templates_dir), trim_blocks=True, lstrip_blocks=True)
	env.filters["VersionV"] = FilterVersionV
	env.filters["VersionI"] = FilterVersionI
	for file_name in file_names:
		output_file = os.path.join(src_dir, file_name)
		t = env.get_template(f"{file_name}.j2")
		with open(output_file, "w") as f:
			f.write(t.render(fields))
