# OCCT-AutoCAD Project — 开发规范

本文档概述项目开发的命名规范、编码风格、界面设计准则、功能需求与开发里程碑，供团队统一执行。

**项目概述**
- **目标**: 基于 Open CASCADE Technology (OCCT) 构建一个轻量级的 CAD 应用，具备文档管理、基本建模（线、圆、矩形、圆弧、样条等）、选择/变换、DXF/STEP 读写与插件扩展能力。
- **代码布局**: 源码放在 `src/`，公共头放在 `include/occt_autocad/`，示例在 `examples/`，测试在 `tests/`。

**命名规范**
- **文件**: 与类型保持一致，使用 PascalCase 对应主要类（例如 `Document.h` / `Document.cpp`、`MainWindow.h` / `MainWindow.cpp`）。工具/脚本或配置文件使用小写加下划线（例如 `generate_bindings.py`）。
- **命名空间**: 使用 `occt_autocad`（小写下划线）。
- **类**: PascalCase（UpperCamelCase），例如 `Document`, `CommandManager`。
- **接口/抽象类**: 不使用 `I` 前缀；用后缀或文档说明（例如 `PluginInterface`）。
- **方法/函数**: lowerCamelCase（例如 `openDocument()`, `addPrimitive()`）。
- **成员变量**: 使用 `m_` 前缀与 lowerCamelCase（例如 `m_activeDocument`）。
- **局部变量**: lower_case_with_underscores 或 lowerCamelCase（团队内保持一致，推荐 `lower_case_with_underscores`）。
- **常量**: 使用 `kCamelCase`（例如 `kMaxUndoSteps`）或 `k_upper_snake` 保持团队一致性。
- **CMake 目标/变量**: 大写与下划线用于变量（例如 `OCCT_DIR`），目标名使用 `occt_autocad_<module>`（例如 `occt_autocad_core`）。

**编码风格 & 格式化**
- **语言标准**: 使用 `C++17`（在 `CMakeLists.txt` 中设置 `target_compile_features`）。
- **格式化工具**: 使用 `clang-format`，仓库根目录放置 `.clang-format`（基于 Google 或 LLVM 风格，按需微调）。
- **静态检查**: 推荐 `clang-tidy`，在 CI 中开启常用检查（现代化建议、性能、易错模式）。
- **注释与文档**: 头文件对外 API 使用 Doxygen 风格注释；实现文件内对复杂算法写清楚思路。
- **异常与错误处理**: 避免抛出裸指针异常；优先使用 `std::optional` / `Result` 风格或 error codes；对外 API 明确错误返回。

**Qt 与 UI 代码约定**
- **信号/槽**: 信号使用 lowerCamelCase（例如 `selectionChanged()`），槽名以 `on` 开头（例如 `onObjectSelected()`）。
- **UI 文件**: 以 `MainWindow.ui`（如果使用 Qt Designer）或对应类 `MainWindow`。界面类放 `ui/` 或 `src/ui/`。
- **线程与渲染**: 渲染与 OCCT 图形上下文应在专用渲染线程或按 Qt 的线程模型运行，禁止在 GUI 线程执行长时间阻塞操作。

**界面设计规范（高层）**
- **布局**: 主窗口采用单文档或多文档选项（SINGLE DOCUMENT 默认，支持标签页式多文档在未来扩展）。左侧为树/图层面板，右侧为属性面板，顶部工具栏包含常用命令，中心为视口（Viewport）。
- **视口交互**:
  - 鼠标左键: 选择/窗口选择（按住 Shift 追加选择）。
  - 鼠标中键/滚轮: 平移/缩放。
  - 鼠标右键: 右键菜单/上下文操作。
  - 旋转（如果 3D）: Alt + 左键拖动 或 专用轨迹球控件。
- **选择反馈**: 选中对象高亮、显示控制点/抓手，浮动提示（尺寸/坐标）。
- **键盘快捷键**: 常用操作提供可配置快捷键（例如 `Ctrl+O` 打开，`Ctrl+Z` 撤销）。

**功能需求（最小可交付 MVP）**
- 文档管理: 新建/打开/保存/另存为（内部格式 + DXF/STEP 导入导出）。
- 基本绘图命令: 线、圆、圆弧、矩形、样条、文字（文本对象）。
- 编辑命令: 移动、旋转、缩放、镜像、复制、删除。
- 选择系统: 单选、多选、窗口/框选、按层/按类型过滤。
- 图层/属性: 基本图层管理、对象属性面板（颜色、线型、图层）。
- Undo/Redo: 可配置的撤销深度（建议 `kMaxUndoSteps`）。
- IO: DXF（读/写简要支持常用实体）和 STEP（读）导入。
- 渲染: 使用 OCCT 的视图/渲染套件，支持线框与带着色渲染模式。
- 插件接口: 提供 `PluginInterface`，允许第三方扩展命令与工具栏按钮。

**模块划分（建议）**
- `app/`：应用启动、配置、单例与主循环。
- `ui/`：窗口、面板、工具条、对话框。
- `core/`：Document、对象模型、层与属性管理。
- `view/`：Viewport、选择、渲染桥接。
- `commands/`：命令体系、撤销/重做栈。
- `geometry/`：几何创建辅助、转换工具。
- `io/`：DXF/STEP 读写器。
- `plugins/`：插件加载与接口定义。

**开发计划（建议里程碑）**
- Sprint 0 (1 周): 项目骨架、CMake 配置、基础 `MainWindow` 与 `Viewport`。
- Sprint 1 (2 周): `Document` 模型、简单绘图命令（线、圆）、基本渲染与选择。
- Sprint 2 (2 周): 编辑命令（移动/复制/删除）、Undo/Redo、属性面板、图层。
- Sprint 3 (2 周): DXF 导入/导出 基础、STEP 读取、IO 测试。
- Sprint 4 (2 周): 插件接口与示例插件、UI 改善、快捷键配置。
- Sprint 5 (1 周): 测试覆盖、CI 配置、打包说明与发布候选。

**测试与 CI 建议**
- 单元测试：用 `Catch2` 或 `GoogleTest` 编写核心逻辑测试（`tests/`）。
- 集成测试：使用 `CTest` 运行构建 + 部分 UI/渲染启动验证（非交互式）。
- CI: 使用 GitHub Actions 或 Azure Pipelines，至少在 Windows x64 和 Ubuntu 上构建并运行单元测试。

**附加建议**
- 使用可配置的日志（例如 `spdlog`）而非 `printf`。
- 在根目录添加 `.editorconfig`、`.clang-format` 和 `CONTRIBUTING.md`（见仓库内）。

如需我把此文档拆分为多份（命名规范、编码风格、UI 指南、需求规格书），我可以继续按模块生成独立文件并提交 PR。
