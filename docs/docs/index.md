# charwidth 帮助文档

## 概述
charwidth 是一个 wcwidth 的 C/C++ 轻量级跨平台实现

## 功能特点
- 轻量级 Header-Only 库，针对性极强，只用于获取字符宽度，没有任何多余数据和代码
- 支持 7.0.0 及以上版本 **Unicode 标准** [^unicode home page] [^unicode character database]
    - 可通过[宏开关](api/macro.md#unicode)静态选择 **Unicode 标准** 的版本，以尽可能减小最终二进制文件体积
    - 可通过函数动态设置 **Unicode 标准** 的版本，以支持程序运行期的灵活使用
- 标准兼容性全面，覆盖常用 C/C++ 标准
    - C89/C90 及以上
    - C++98 及以上
- 跨平台，目前测试通过的平台环境包括
    - ubuntu gcc
	- macos apple clang
	- windows msvc
	- windows mingw64 gcc

## 暂时不支持的功能
- 目前暂不支持对 emoji sequences [^emoji sequences] [^database emoji]、emoji ZWJ sequences [^emoji ZWJ sequences] [^database emoji] 的宽度获取


[^unicode home page]: [unicode home page](https://home.unicode.org/)
[^unicode character database]: [unicode character database](https://www.unicode.org/Public/)
[^emoji sequences]: [emoji sequences](https://www.unicode.org/reports/tr51/#Emoji_Sequences)
[^emoji ZWJ sequences]: [emoji ZWJ sequences](https://www.unicode.org/reports/tr51/#Emoji_ZWJ_Sequences)
[^database emoji]: [database emoji](https://www.unicode.org/Public/draft/emoji/)

