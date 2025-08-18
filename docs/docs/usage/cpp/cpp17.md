---
title: C++17 及以上标准
---

# {{ page.meta.title }}

代码示例：
```C++ linenums="1"
#include <iostream>
#include <charwidth/charwidth_cpp17.h>

int main(void) {
	charwidth::u32 c = 0x1234;

	charwidth::SetVersion(charwidth::V_16_0_0);
	charwidth::TreatAmbiguousAsNarrow();

	int w = charwidth::CharWidth(c);

	std::cout << "width of 0x" << std::hex << c << ": " << w << std::endl;

	return 0;
}
```

cmake 示例：
```cmake linenums="1"
SET(CMAKE_CXX_STANDARD 17)
...
FIND_LIBRARY(charwidth)
...
TARGET_COMPILE_OPTIONS(<target> CW_ENABLE_ALL=0 CW_ENABLE_8_0_0=1 CW_ENABLE_16_0_0=1)
TARGET_LINK_LIBRARIES(<target> charwidth::charwidth)
```
