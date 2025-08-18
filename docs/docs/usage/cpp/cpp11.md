---
title: C++11/C++14 标准
---

# {{ page.meta.title }}

代码示例：
```C++ linenums="1"
#include <iostream>
#include <charwidth/charwidth_cpp11.h>

int main(void) {
	charwidth::u32 c = 0x1234;

	charwidth::SetVersion(charwidth::V_11_0_0);
	charwidth::TreatAmbiguousAsWide();

	int w = charwidth::CharWidth(c);

	std::cout << "width of 0x" << std::hex << c << ": " << w << std::endl;

	return 0;
}
```

cmake 示例：
```cmake linenums="1"
SET(CMAKE_CXX_STANDARD 11)
...
FIND_LIBRARY(charwidth)
...
TARGET_COMPILE_OPTIONS(<target> CW_ENABLE_7_0_0=0 CW_ENABLE_8_0_0=0)
TARGET_LINK_LIBRARIES(<target> charwidth::charwidth)
```
