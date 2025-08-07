// Copyright (c) 2025 didarpin
// SPDX-License-Identifier: MIT

#include <charwidth_cpp11.h>

#include "s_cpp.h"

int main(void) {
	ASSERT(charwidth::CharWidth(0) == 0);
	ASSERT(charwidth::CharWidth(1) == 0);
	ASSERT(charwidth::CharWidth(U'a') == 1);
	ASSERT(charwidth::CharWidth(0x7f) == 0);
	ASSERT(charwidth::CharWidth(U'世') == 2);
	ASSERT(charwidth::CharWidth(0x1f191) == 2);
	std::cerr << "test_cpp11 pass" << std::endl;
	return 0;
}
