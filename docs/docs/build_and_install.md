---
title: 构建和安装
---

# {{ page.meta.title }}

本项目使用 cmake 进行构建和安装

## :octicons-square-fill-16: 构建和安装 charwidth Header-Only 库
```sh linenums="1"
mkdir build
cmake \
	-D CMAKE_INSTALL_PREFIX=<install_dir> \
	-D charwidth_project=OFF \
	-D charwidth_project_lib=ON \
	-B build \
	-S .
cmake --build build
cmake --install build
```

## :octicons-square-fill-16: 运行测试

=== "单配置生成器"
    ```sh linenums="1"
    mkdir build
    cmake \
    	-D CMAKE_BUILD_TYPE=Release \
    	-D charwidth_project=OFF \
    	-D charwidth_project_test_c90=ON \
    	-D charwidth_project_test_c99=ON \
    	-D charwidth_project_test_cpp98=ON \
    	-D charwidth_project_test_cpp11=ON \
    	-D charwidth_project_test_cpp17=ON \
    	-B build \
		-S .
    cmake --build build
    ctest --test-dir build -V
    ```

=== "多配置生成器"
    ```sh linenums="1"
    mkdir build
    cmake \
    	-D charwidth_project=OFF \
    	-D charwidth_project_test_c90=ON \
    	-D charwidth_project_test_c99=ON \
    	-D charwidth_project_test_cpp98=ON \
    	-D charwidth_project_test_cpp11=ON \
    	-D charwidth_project_test_cpp17=ON \
    	-B build \
		-S .
    cmake --build build --config Release
    ctest --test-dir build -C Release -V
    ```
