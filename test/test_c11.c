// Copyright (c) 2025 didarpin
// SPDX-License-Identifier: MIT

#include "s_c.h"
#include "../src/charwidth_c11.h"

int main() {
	ASSERT(CW_CharWidth(0) == 0);
	ASSERT(CW_CharWidth(1) == 0);
	ASSERT(CW_CharWidth('a') == 1);
	ASSERT(CW_CharWidth(0x7f) == 0);
	ASSERT(CW_CharWidth(0x4e16) == 2);
	ASSERT(CW_CharWidth(0x1f191) == 2);
	fprintf(stderr, "test_c11 pass\n");
	return 0;
}
