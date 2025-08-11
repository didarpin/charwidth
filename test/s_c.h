/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/ 

#pragma once

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(condition)										\
	do {														\
		if (!(condition)) {										\
			fprintf(stderr, "[ASSERT FAILED] %s:%d | %s\n",		\
				__FILE__, __LINE__, #condition);				\
			exit(1);											\
		}														\
	} while(0)
