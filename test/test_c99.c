/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/charwidth_c99.h"

#define ASSERT(condition, ...)											\
	do {																\
		if (!(condition)) {												\
			printf("[ASSERT FAILED] %s:%d | ", __FILE__, __LINE__);		\
			printf(__VA_ARGS__);										\
			printf("\n");												\
			exit(1);													\
		}																\
	} while(0)

char const* data_dir;

void TestV(CW_Version cm_version, char const* s_version);
void TestF(CW_Version cm_version, int width, char const* file);
void SPrintF(char* str, size_t size, char const* format, ...);

int main(int argc, char** argv) {
	ASSERT(argc == 2, "invalid argument");
	data_dir = argv[1];
	ASSERT(strlen(data_dir) < 900, "data_dir too long");

	TestV(CW_V_7_0_0, "7.0.0");
	TestV(CW_V_8_0_0, "8.0.0");
	TestV(CW_V_9_0_0, "9.0.0");
	TestV(CW_V_10_0_0, "10.0.0");
	TestV(CW_V_11_0_0, "11.0.0");
	TestV(CW_V_12_0_0, "12.0.0");
	TestV(CW_V_13_0_0, "13.0.0");
	TestV(CW_V_14_0_0, "14.0.0");
	TestV(CW_V_15_0_0, "15.0.0");
	TestV(CW_V_15_1_0, "15.1.0");
	TestV(CW_V_16_0_0, "16.0.0");
	TestV(CW_V_17_0_0, "17.0.0");

	printf("test_c99 passed\n");
	return 0;
}

void TestV(CW_Version cm_version, char const* s_version) {
	char file[1024];

	CW_SetVersion(cm_version);
	CW_SetAmbiguousWidth(2);
	
	SPrintF(file, sizeof(file), "%s/%s_0.dat", data_dir, s_version);
	TestF(cm_version, 0, file);

	SPrintF(file, sizeof(file), "%s/%s_1.dat", data_dir, s_version);
	TestF(cm_version, 1, file);

	SPrintF(file, sizeof(file), "%s/%s_2.dat", data_dir, s_version);
	TestF(cm_version, 2, file);

	SPrintF(file, sizeof(file), "%s/%s_ambiguous.dat", data_dir, s_version);
	TestF(cm_version, 2, file);
}

void TestF(CW_Version cm_version, int width, char const* file) {
#define N 1024
	FILE* fd;
	cw_c32 cs[N];
	size_t i, size;

	fd = fopen(file, "rb");
	ASSERT(fd != NULL, "open file error: %s", file);

	while (1) {
		size = fread(cs, 4, N, fd);
		if (size < N) ASSERT(feof(fd), "read file error: %s", file);
		for (i = 0; i < size; ++i) {
			ASSERT(CW_CharWidth(cs[i]) == width, "CharWidth error: 0x%x, %d", cs[i], width);
		}
		if (size < N) break;
	}

	fclose(fd);
#undef N
}

void SPrintF(char* str, size_t size, char const* format, ...) {
	va_list ap;
	va_start(ap, format);
#if _MSC_VER
	vsprintf_s(str, size, format, ap);
#else
	vsprintf(str, format, ap);
#endif
}
