# OCCT-Example 项目

## 项目概述
本项目是一个基于 Open CASCADE Technology (OCCT) 的示例项目，旨在展示如何使用 OCCT 进行 3D 建模、几何处理和可视化。该项目适用于开发人员、研究人员和 CAD 系统开发者。


## 环境要求
- **操作系统**: Windows 10 或更高版本
- **编译器**: Visual Studio 2019 或更高版本
- **依赖库**: 
  - Open CASCADE Technology (OCCT) 7.9.1 
  - Qt 5.14.2 或更高版本
- **构建工具**: CMake 3.16 或更高版本

## 安装与构建
1. 克隆项目到本地：
   ```powershell
   git clone https://github.com/xxx/OCCT-Example.git
   cd OCCT-Example
   ```
2. 使用 CMake 生成构建文件：
   ```powershell
   mkdir build
   cd build
   cmake -G "Visual Studio 16 2019" -A x64 ..
   ```
3. 使用 Visual Studio 打开生成的解决方案文件并构建项目。

## 示例项目
- [Sample01](Sample01/README.md): 一个基本的 OCCT Qt 示例，展示了如何创建基本 3D 形状并进行视图控制。

## 贡献指南
我们欢迎任何形式的贡献！如果您有改进建议或发现 bug，请提交 issue 或 pull request。

## 许可证
本项目采用 GNU 通用公共许可证 v3.0 (GPLv3)。详情请参阅 [LICENSE](LICENSE) 文件。