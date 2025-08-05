// Copyright (c) 2025 didarpin
// SPDX-License-Identifier: MIT

#pragma once

#include <iostream>
#include <cstdlib>

#define ASSERT(condition)									\
	do {													\
		if (!(condition)) {									\
			std::cerr << "[ASSERT FAILED] "					\
			          << __FILE__ << ":" << __LINE__		\
			          << " | " << #condition << std::endl;	\
			std::exit(1);									\
		}													\
	} while (0)
