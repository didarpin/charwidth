/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/

#include <cstdio>
#include <fstream>
#include <string>

#include "../src/charwidth_cpp98.h"

#define ASSERT(condition, fmt)												\
	do {																	\
		if (!(condition)) {													\
			std::printf("[ASSERT FAILED] %s:%d | ", __FILE__, __LINE__);	\
			std::printf fmt;												\
			std::printf("\n");												\
			exit(1);														\
		}																	\
	} while(0)

std::string data_dir;

void TestV(charwidth::Version cm_version, std::string const& s_version);
void TestF(charwidth::Version cm_version, int width, std::string const& file);

int main(int argc, char** argv) {
	ASSERT(argc == 2, ("invalid argument"));
	data_dir = argv[1];

	TestV(charwidth::V_7_0_0, "7.0.0");
	TestV(charwidth::V_8_0_0, "8.0.0");
	TestV(charwidth::V_9_0_0, "9.0.0");
	TestV(charwidth::V_10_0_0, "10.0.0");
	TestV(charwidth::V_11_0_0, "11.0.0");
	TestV(charwidth::V_12_0_0, "12.0.0");
	TestV(charwidth::V_13_0_0, "13.0.0");
	TestV(charwidth::V_14_0_0, "14.0.0");
	TestV(charwidth::V_15_0_0, "15.0.0");
	TestV(charwidth::V_15_1_0, "15.1.0");
	TestV(charwidth::V_16_0_0, "16.0.0");
	TestV(charwidth::V_17_0_0, "17.0.0");

	printf("test_cpp98 passed\n");
	return 0;
}

void TestV(charwidth::Version cm_version, std::string const& s_version) {
	std::string file;

	charwidth::SetVersion(cm_version);
	charwidth::SetAmbiguousWidth(1);
	
	file = data_dir + "/" + s_version + "_0.dat", 
	TestF(cm_version, 0, file);

	file = data_dir + "/" + s_version + "_1.dat", 
	TestF(cm_version, 1, file);

	file = data_dir + "/" + s_version + "_2.dat", 
	TestF(cm_version, 2, file);

	file = data_dir + "/" + s_version + "_ambiguous.dat", 
	TestF(cm_version, 1, file);
}

void TestF(charwidth::Version cm_version, int width, std::string const& file) {
	std::ifstream ifs;

	ifs.open(file.c_str(), std::ios_base::in | std::ios_base::binary);
	ASSERT(ifs.is_open(), ("open file error: %s", file.c_str()));

	unsigned int const n = 1024;
	charwidth::c32 cs[n];

	while (1) {
		ifs.read(reinterpret_cast<char*>(cs), n * 4);
		if (!ifs) ASSERT(ifs.eof(), ("read file error: %s", file.c_str()));
		size_t size = ifs.gcount() / 4;
		for (size_t i = 0; i < size; ++i) {
			ASSERT(charwidth::CharWidth(cs[i]) == width, ("CharWidth error: 0x%x, %d", cs[i], width));
		}
		if (!ifs) break;
	}

	ifs.close();
}
