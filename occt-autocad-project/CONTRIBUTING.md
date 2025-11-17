# 贡献指南

感谢你为 OCCT-AutoCAD 项目做贡献！为保持代码质量和协作效率，请遵守以下流程与要求。

**分支策略**
- `main` / `master`: 仅存放可发布的稳定版本。
- `develop`: 日常开发主分支（可选）。
- 功能分支: 使用 `feature/<短描述>`（如 `feature/dxf-import`）。
- 修复分支: 使用 `fix/<issue-number>-short-desc`。

**提交信息**
- 使用简洁、清晰的提交信息，推荐遵循 Conventional Commits 风格：
  - `feat: add dxf import for LINE and CIRCLE`
  - `fix: correct memory leak in Viewport`
  - `docs: update development guidelines`

**代码风格与格式化**
- 在提交前运行格式化工具：

```powershell
# 在 Windows PowerShell 下（示例）
clang-format -i <path-to-file>
```

- 遵循仓库 `.clang-format` 与 `.editorconfig`（若存在）。

**静态检查与测试**
- 在提交前运行单元测试（若修改核心逻辑）：

```powershell
mkdir -p build; cd build; cmake .. -G "Visual Studio 16 2019" -A x64; cmake --build . --config Release; ctest -C Release
```

- 运行 `clang-tidy` / `cppcheck`（建议在本地或 CI 中）以捕获常见问题。

**Pull Request 要求**
- 每个 PR 请关联 issue（如果有）。
- PR 应包含变更说明、测试覆盖情况与必要的截图（UI 变更）。
- 至少一名同伴审查并通过 CI 后方可合并。

**代码审查重点**
- 可读性：清晰函数边界与合理命名。
- 正确性：边界条件、错误处理、资源释放。
- 性能：避免不必要的拷贝或重复计算。
- API 兼容性：公共头变更需慎重并写明迁移说明。

如果你不确定规范如何应用到特定实现，欢迎在 issue 中讨论或直接发起 PR 标注为 WIP。

---

需要我为仓库添加一个 `.clang-format` 示例、`CI` 配置模板（GitHub Actions）或本地开发启动脚本吗？我可以继续创建这些文件并提交。 
