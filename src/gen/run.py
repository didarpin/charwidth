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
work_dir = str(cf_dir.parent.parent)
src_dir = os.path.join(work_dir, "src");
templates_dir = os.path.join(src_dir, "gen", "templates");
tmp_dir = os.path.join(work_dir, "tmp");

version = "17.0.0"
unicode_data_url = f"https://unicode.org/Public/{version}/ucd/UnicodeData.txt"
eaw_url = f"https://unicode.org/Public/{version}/ucd/EastAsianWidth.txt"
emoji_data_url = f"https://unicode.org/Public/{version}/ucd/emoji/emoji-data.txt"

max_codepoint = 0x10ffff

unicode_data = []
eaw_data = []
emoji_data = []

########

class CodePoint:
	def __init__(self, codepoint):
		self.codepoint = codepoint
		self.width = 0


def ReadFile(url):
	name = url.rsplit("/", 1)[-1]
	path = os.path.join(tmp_dir, name)
	if not os.path.isfile(path):
		print(f"Downloading {name}\n")
		urlretrieve(url, path)
	with open(path, "rb") as f:
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
	def InWidth0Rgs(cp):
		for (cp_min, cp_max) in width0_rgs:
			if cp_min <= cp <= cp_max: return True
		return False

	width0_rgs = [(0xd800, 0xdfff), (0xfdd0, 0xfdef), (0x1160, 0x11ff), (0xd7b0, 0xd7ff)]
	for i in range(0, 17):
		cp = 0x10000 * i + 0xfffe
		width0_rgs.append((cp, cp + 1))

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
			if InWidth0Rgs(cp): continue
			if fields[2] in ["Cc", "Cf", "Zl", "Zp", "Mn", "Mc", "Me"]: continue
			cps[cp].width = 1


def SetEawWidths(cps):
	for line in eaw_data:
		rg, prop = ParseEawOrEmojiLine(line)
		# A : Ambiguous
		# F : Fullwidth
		# H : Halfwidth,
		# N : Neutral(= Not East Asian)
		# Na: Narrow
		# W : Wide
		if prop in ["A", "H", "Na"]:
			SetRangeWidth(rg, 1, cps)
		elif prop in ["F", "W"]:
			SetRangeWidth(rg, 2, cps)

	rgs = (
		(0x3400, 0x4dbf),
		(0x4e00, 0x9fff),
		(0xf900, 0xfaff),
		(0x20000, 0x2fffd),
		(0x30000, 0x3fffd),
	)

	for rg in rgs:
		SetRangeWidth(rg, 2, cps)


def SetEmojiWidths(cps):
	for line in emoji_data:
		rg, prop = ParseEawOrEmojiLine(line)
		if prop == "Emoji_Presentation":
			for cp in range(rg[0], rg[1] + 1):
				if 0x1f1e6 <= cp <= 0x1f1ff:
					cps[cp].width = 1
				else:
					cps[cp].width = 2


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


def ParseEawOrEmojiLine(eaw_line):
	line = eaw_line.split("#", 1)[0]
	fields = line.split(";")
	return (ToRange(fields[0]), fields[1].strip())


def ReadData():
	global unicode_data, eaw_data, emoji_data
	unicode_data = ReadFile(unicode_data_url)
	eaw_data = ReadFile(eaw_url)
	emoji_data = ReadFile(emoji_data_url)


def MakeCodepoints():
	cps = [CodePoint(cp) for cp in range(max_codepoint + 1)]
	SetGeneralWidths(cps)
	SetEawWidths(cps)
	SetEmojiWidths(cps)
	return cps


if __name__ == "__main__":
	os.makedirs(tmp_dir, exist_ok=True)
	ReadData()
	cps = MakeCodepoints()

	fields = {
		"width0": MergeCodepoint((cp for cp in cps if cp.width == 0)),
		"width1": MergeCodepoint((cp for cp in cps if cp.width == 1)),
		"width2": MergeCodepoint((cp for cp in cps if cp.width == 2)),
	}

	env = Environment(loader=FileSystemLoader(templates_dir), trim_blocks=True, lstrip_blocks=True)
	for root, dirs, files in os.walk(templates_dir):
		for file_name in files:
			if not file_name.endswith(".j2"): continue

			output_name = f"charwidth_{file_name[:-3]}"
			output_path = os.path.join(src_dir, output_name)

			t = env.get_template(file_name)

			with open(output_path, "w") as f:
				f.write(t.render(fields))

