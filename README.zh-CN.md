<h1 align="center">OCCT-Examples</h1>

<p align="center">基于 Open CASCADE Technology (OCCT) 与 Qt 5 的渐进式 C++17 示例集合，涵盖基础 3D 视口渲染到类 AutoCAD 文档架构原型。</p>

<p align="center">
  <a href="./README.md">English</a> | <a href="./README.zh-CN.md">简体中文</a>
</p>

<p align="center"><img src="https://img.shields.io/badge/C%2B%2B-17-3776AB?style=flat-square" alt="C++17"> <img src="https://img.shields.io/badge/OCCT-7.9.1-3776AB?style=flat-square" alt="OCCT 7.9.1"> <img src="https://img.shields.io/badge/Qt-5.14.2%2B-3776AB?style=flat-square" alt="Qt 5.14.2+"> <img src="https://img.shields.io/badge/Platform-Windows-4B5563?style=flat-square" alt="Platform: Windows"> <a href="./LICENSE"><img src="https://img.shields.io/badge/License-GPL--3.0-22C55E?style=flat-square" alt="License: GPL-3.0"></a></p>

OCCT-Examples 收录了四个独立的 CMake 子项目，从最小化的 Qt 5 + OCCT 三维视图起步，逐步演进到基于 JSON 配置的命令与实体系统，以及具备撤销/重做命令栈、JSON 持久化和 Catch2 单元测试的类 AutoCAD CAD 原型。

## 核心亮点

| 亮点 | 价值说明 |
|---|---|
| 渐进式 OCCT + Qt 5 学习路径 | 从单窗口 3D 视口（`Sample01`）过渡到命令分发（`Sample02`）与实体持久化（`Sample03`），按阶段拆解复杂度。 |
| JSON 驱动菜单与场景序列化 | `Sample02` 与 `Sample03` 通过 `resources/config/ui_config.json` 动态构建菜单，`Sample03` 支持将 3D 实体场景保存与重新加载为 JSON 文件。 |
| 类 AutoCAD 数据库与命令模型 | `occt-autocad-project` 将 `DBObject`、`Entity`、`Table`、`Database` 数据层与 `CommandManager` 撤销/重做历史及 `Document` 持久化解耦。 |
| 内置 Catch2 单元测试套件 | `occt-autocad-project/tests` 通过 CTest 覆盖数据库操作、实体命令、命令组与文档序列化测试。 |

## 架构概览

仓库根目录不包含顶层 `CMakeLists.txt`，四个子目录均为独立构建的 CMake 项目，整体按功能复杂度逐级演进：

```text
┌───────────────────┐     ┌────────────────────────────────────────┐
│     Sample01      │     │                Sample02                │
│  MainWindow       │────▶│  UIConfig (JSON) ──▶ ActionManager     │
│  Viewport (OCCT)  │     │  ViewportManager ──▶ Viewport (OCCT)   │
└───────────────────┘     └────────────────────────────────────────┘
                                              │
                                              ▼
┌─────────────────────────────────────────┐   ┌──────────────────────────────────────┐
│          occt-autocad-project           │   │               Sample03               │
│  UI / Viewport ◀──▶ CommandManager      │◀──│  UIConfig / FileAction (JSON I/O)    │
│        │                 │              │   │  EntityFactory ──▶ 3D Entities       │
│        ▼                 ▼              │   │  Viewport (OCCT + Coin3D / SoQt)     │
│  Document / Database (Table, Entities)  │   └──────────────────────────────────────┘
│        │                                │
│        ▼                                │
│  IO (JSON, DXFReader/Writer, STEPReader)│
└─────────────────────────────────────────┘
```

| 子项目 | 核心内容 | 主要依赖 |
|---|---|---|
| [`Sample01`](./Sample01) | 基础 3D 图元创建（立方体、圆柱、圆锥、圆环、球体）、视口交互控制及线框/着色模式切换 | C++17、CMake 3.16+、Qt 5、OCCT |
| [`Sample02`](./Sample02) | JSON 菜单配置（`ui_config.json`）、`ActionFactory` / `ActionManager`、`ViewportManager` 与随机测试（`RandomTestAction`） | C++17、CMake 3.16+、Qt 5、OCCT |
| [`Sample03`](./Sample03) | 模块化实体类（`Box`、`Cylinder`、`Frustum`、`Sphere`、`Torus`）、JSON 场景打开/保存（`FileAction`）与清空（`ClearAction`） | C++17、CMake 3.16+、Qt 5、OCCT、Coin3D、SoQt |
| [`occt-autocad-project`](./occt-autocad-project) | `DBObject` / `Entity` / `Table` / `Database` 数据模型、撤销/重做 `CommandManager`、DXF/STEP 读写及 Catch2 测试 | C++17、CMake 3.14+、OCCT、Qt 5、`nlohmann/json`（FetchContent）、Catch2（测试） |

## 快速安装

### 环境要求

- **操作系统**：Windows 10 或更高版本（x64）
- **编译器**：Visual Studio 2019 或更高版本（MSVC，支持 C++17）
- **构建工具**：CMake 3.16 或更高版本
- **依赖库**：
  - Open CASCADE Technology (OCCT) 7.9.1
  - Qt 5.14.2 或更高版本（`Core`、`Gui`、`Widgets`）
  - Coin3D（`Coin4`）与 SoQt（`SoQt1.6.0`）——仅 `Sample03` 需要

### 克隆仓库

```powershell
git clone https://github.com/zly258/OCCT-Examples.git
cd OCCT-Examples
```

## 快速开始

### 构建并运行 Sample01

1. 打开 `Sample01/CMakeLists.txt`，将 `Qt5_DIR`、`OCCT_INCLUDE_DIR` 和 `OCCT_LIB_DIR` 修改为本机实际的 Qt 5 与 OCCT 安装路径。
2. 使用 CMake 配置并编译 `Sample01`：

```powershell
cd Sample01
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release
```

3. 运行生成的 `Release\Sample01.exe`（请确保 Qt 5 与 OCCT 的 `bin` 目录已加入 `PATH`，以便运行时加载动态链接库）。启动后将打开包含 OCCT 3D 视口的 Qt 主窗口，可创建基础几何体、切换线框/着色模式并进行缩放、平移和旋转操作。

### 运行 occt-autocad-project 单元测试

`occt-autocad-project` 会通过 CMake `FetchContent` 自动拉取 `nlohmann/json` v3.11.2 和 `Catch2` v2.13.10：

```powershell
cd occt-autocad-project
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 -DOCCT_DIR="C:/path/to/occt" ..
cmake --build . --config Release
ctest -C Release --output-on-failure
```

## 配置与集成

各子项目独立维护构建脚本，依赖路径按子项目分别配置：

| 子项目 | 配置方式 | 需配置的变量 |
|---|---|---|
| `Sample01`、`Sample02` | 在 `CMakeLists.txt` 中直接修改路径变量 | `Qt5_DIR`、`OCCT_INCLUDE_DIR`、`OCCT_LIB_DIR` |
| `Sample03` | 在 `CMakeLists.txt` 中修改路径变量（MSVC 下构建后自动复制 Coin3D/SoQt DLL） | `Qt5_DIR`、`OCCT_INCLUDE_DIR`、`OCCT_LIB_DIR`、`COIN3D_ROOT`、`SOQT_ROOT` |
| `occt-autocad-project` | CMake 缓存变量 + `FetchContent`（`nlohmann/json` v3.11.2、`Catch2` v2.13.10） | `-DOCCT_DIR=<path-to-occt>` |

## 文档导航

| 主题 | 内容说明 | 链接 |
|---|---|---|
| Sample01 入门 | 基础 OCCT + Qt 5 示例的功能特性、环境要求与构建步骤 | [Sample01/README.md](./Sample01/README.md) |
| CAD 原型概览 | `occt-autocad-project` 的模块结构、功能与构建说明 | [occt-autocad-project/README.md](./occt-autocad-project/README.md) |
| CAD 数据模型设计 | `DBObject`、`Entity`、`Table`、`Database`、命令事务与插件扩展设计 | [occt-autocad-project/docs/ARCHITECTURE.md](./occt-autocad-project/docs/ARCHITECTURE.md) |
| 开发规范 | 命名约定、C++17/Qt 编码规范、界面交互设计与模块划分 | [occt-autocad-project/docs/DEVELOPMENT_GUIDELINES.md](./occt-autocad-project/docs/DEVELOPMENT_GUIDELINES.md) |
| 贡献流程 | 分支策略、Conventional Commits 提交规范、格式化与 CTest 检查 | [occt-autocad-project/CONTRIBUTING.md](./occt-autocad-project/CONTRIBUTING.md) |

## 参与贡献

欢迎通过 GitHub Issue 与 Pull Request 提交改进或问题反馈。分支命名、提交规范、`clang-format` 格式化及 CTest 验证步骤请参阅 [occt-autocad-project/CONTRIBUTING.md](./occt-autocad-project/CONTRIBUTING.md)。

## 许可证

本仓库采用 GNU General Public License v3.0 (GPL-3.0) 许可证，详情请参阅 [LICENSE](./LICENSE)。
