/*
	Copyright (c) 2025 didarpin
	SPDX-License-Identifier: MIT
*/

#pragma once

void SPrintF(char* str, size_t size, char const* format, ...) {
	va_list ap;
	va_start(ap, format);
#if _MSC_VER
	vsprintf_s(str, size, format, ap);
#else
	vsprintf(str, format, ap);
#endif
}

FILE* FOpen(char const* pathname, char const* mode) {
#if _MSC_VER
	FILE* fd;
	errno_t r = fopen_s(&fd, pathname, mode);
	return r ? NULL : fd;
#else
	return fopen(pathname, mode);
#endif
}
