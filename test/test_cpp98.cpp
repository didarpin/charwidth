// Copyright (c) 2025 didarpin
// SPDX-License-Identifier: MIT

#include "s_cpp.h"
#include "../src/charwidth_cpp98.h"

int main(void) {
	ASSERT(charwidth::CharWidth(0) == 0);
	ASSERT(charwidth::CharWidth(1) == 0);
	ASSERT(charwidth::CharWidth(0x7f) == 0);
	ASSERT(charwidth::CharWidth(0x1f191) == 2);
	std::cerr << "test_cpp98 passed" << std::endl;
	return 0;
}
