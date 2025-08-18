---
title: 函数 CharWidth
---

# {{ page.meta.title }}

## :octicons-square-fill-16: 函数说明

位于 namespace charwidth 内

获取字符宽度

在调用本函数前，应先 :

- 调用 [SetVersion](SetVersion.md) 设置当前 **Unicode 标准** 的版本
- 调用 [TreatAmbiguousAsWide](TreatAmbiguousAsWide.md) 或 [TreatAmbiguousAsNarrow](TreatAmbiguousAsNarrow.md) 设置 **东亚模糊宽度字符** 的宽度

## :octicons-square-fill-16: 函数原型

```C++
// in namespace charwidth
int CharWidth(u32 c);
```

- c : 字符 Unicode 码点对应的数值，例如码点为 U+0030，则传入 0x30
- 返回值 :
    - 0、1、2 : 字符宽度
	- -1 : 出错

