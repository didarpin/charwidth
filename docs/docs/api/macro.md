---
title: 宏
search:
  boost: 2 
---

# {{ page.meta.title }}

## :octicons-square-fill-16: **Unicode 标准** 版本宏开关

```C linenums="1"
CW_ENABLE_ALL
CW_ENABLE_7_0_0
CW_ENABLE_8_0_0
CW_ENABLE_9_0_0
CW_ENABLE_10_0_0
CW_ENABLE_11_0_0
CW_ENABLE_12_0_0
CW_ENABLE_12_1_0
CW_ENABLE_13_0_0
CW_ENABLE_14_0_0
CW_ENABLE_15_0_0
CW_ENABLE_15_1_0
CW_ENABLE_16_0_0
CW_ENABLE_17_0_0
```

- 0 : 关闭版本支持
- 1 : 开启版本支持
- CW_ENABLE_ALL 如果不设置，默认为 1
- CW_ENABLE_<version\> 如果不设置，默认为 CW_ENABLE_ALL

!!! example "例 1 : 开启对所有版本的支持"
    - CW_ENABLE_ALL 设置为 1 或不设置

!!! example "例 2 : 仅开启对 17.0.0 版本的支持"
    - CW_ENABLE_ALL 设置为 0
    - CW_ENABLE_17_0_0 设置为 1

!!! example "例 3 : 仅关闭对 15.1.0 版本的支持"
    - CW_ENABLE_ALL 设置为 1 或不设置
    - CW_ENABLE_15_1_0 设置为 0

