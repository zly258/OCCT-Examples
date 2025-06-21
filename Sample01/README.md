# OCCT Qt 示例 - Sample01

## 功能特性

- 基本 3D 形状创建：
  - 立方体
  - 圆柱体
  - 圆锥体
  - 圆环
  - 球体
- 视图控制：
  - 缩放
  - 平移
  - 旋转
  - 适配所有
- 显示模式：
  - 线框模式
  - 填充模式

## 系统要求

- Qt 5.14.2 (msvc2017_64)
- OpenCASCADE 7.9.1 (vc14_64)
- CMake 3.16+
- Visual Studio 2019 (v142)

## 构建说明

1. 克隆仓库
2. 创建构建目录：
   ```bash
   mkdir build
   cd build
   ```
3. 使用 CMake 配置项目：
   ```bash
   cmake -G "Visual Studio 16 2019" -A x64 ..
   ```
4. 构建项目：
   ```bash
   cmake --build . --config Release
   ```

## 项目结构 