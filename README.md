<h1 align="center">OCCT-Examples</h1>

<p align="center">Progressive C++17 example projects for building 3D CAD viewers and AutoCAD-style document architectures with Open CASCADE Technology (OCCT) and Qt 5.</p>

<p align="center">
  <a href="./README.md">English</a> | <a href="./README.zh-CN.md">简体中文</a>
</p>

<p align="center"><img src="https://img.shields.io/badge/C%2B%2B-17-3776AB?style=flat-square" alt="C++17"> <img src="https://img.shields.io/badge/OCCT-7.9.1-3776AB?style=flat-square" alt="OCCT 7.9.1"> <img src="https://img.shields.io/badge/Qt-5.14.2%2B-3776AB?style=flat-square" alt="Qt 5.14.2+"> <img src="https://img.shields.io/badge/Platform-Windows-4B5563?style=flat-square" alt="Platform: Windows"> <a href="./LICENSE"><img src="https://img.shields.io/badge/License-GPL--3.0-22C55E?style=flat-square" alt="License: GPL-3.0"></a></p>

OCCT-Examples collects four standalone CMake subprojects that progress from a minimal Qt 5 + OCCT 3D viewport to a modular entity-and-action application and an AutoCAD-inspired CAD prototype with undo/redo commands, JSON persistence, and Catch2 unit tests.

## Highlights

| Highlight | Why it matters |
|---|---|
| Step-by-step OCCT + Qt 5 progression | Start with a single-window 3D viewer (`Sample01`) and advance through action dispatch (`Sample02`) and entity persistence (`Sample03`) without wading through a monolithic codebase. |
| JSON-driven UI and scene persistence | `Sample02` and `Sample03` load menu layouts from `resources/config/ui_config.json`, and `Sample03` saves and reloads 3D entity scenes as JSON files. |
| AutoCAD-style database and command model | `occt-autocad-project` separates `DBObject`, `Entity`, `Table`, and `Database` from `CommandManager` undo/redo history and `Document` persistence. |
| Built-in Catch2 unit test suite | `occt-autocad-project/tests` covers database operations, entity commands, command groups, and document serialization via CTest. |

## Architecture

Each top-level directory is an independent CMake project with no root `CMakeLists.txt`. The repository progresses from basic viewport rendering to a layered CAD document architecture:

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

| Subproject | Primary focus | Key dependencies |
|---|---|---|
| [`Sample01`](./Sample01) | Basic 3D primitive creation (box, cylinder, cone, torus, sphere), viewport navigation, and wireframe/shaded modes | C++17, CMake 3.16+, Qt 5, OCCT |
| [`Sample02`](./Sample02) | JSON-configured menus (`ui_config.json`), `ActionFactory` / `ActionManager`, `ViewportManager`, and `RandomTestAction` | C++17, CMake 3.16+, Qt 5, OCCT |
| [`Sample03`](./Sample03) | Modular entity classes (`Box`, `Cylinder`, `Frustum`, `Sphere`, `Torus`), JSON open/save (`FileAction`), and `ClearAction` | C++17, CMake 3.16+, Qt 5, OCCT, Coin3D, SoQt |
| [`occt-autocad-project`](./occt-autocad-project) | `DBObject` / `Entity` / `Table` / `Database` model, undo/redo `CommandManager`, DXF/STEP I/O, and Catch2 tests | C++17, CMake 3.14+, OCCT, Qt 5, `nlohmann/json` (FetchContent), Catch2 (tests) |

## Quick Install

### Prerequisites

- **OS**: Windows 10 or later (x64)
- **Compiler**: Visual Studio 2019 or later (MSVC with C++17 support)
- **Build tool**: CMake 3.16 or later
- **Libraries**:
  - Open CASCADE Technology (OCCT) 7.9.1
  - Qt 5.14.2 or later (`Core`, `Gui`, `Widgets`)
  - Coin3D (`Coin4`) and SoQt (`SoQt1.6.0`) — required only for `Sample03`

### Clone the repository

```powershell
git clone https://github.com/zly258/OCCT-Examples.git
cd OCCT-Examples
```

## Quick Start

### Build and run Sample01

1. Open `Sample01/CMakeLists.txt` and update `Qt5_DIR`, `OCCT_INCLUDE_DIR`, and `OCCT_LIB_DIR` to match your local Qt 5 and OCCT installation paths.
2. Configure and build `Sample01` with CMake:

```powershell
cd Sample01
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 ..
cmake --build . --config Release
```

3. Run the generated `Release\Sample01.exe` binary (ensure your Qt 5 and OCCT `bin` directories are on `PATH` so runtime DLLs can be loaded). The application opens a Qt window with an OCCT 3D viewport where you can create primitives, switch between wireframe and shaded display modes, and zoom, pan, or rotate the scene.

### Run occt-autocad-project unit tests

`occt-autocad-project` fetches `nlohmann/json` v3.11.2 and `Catch2` v2.13.10 automatically via CMake `FetchContent`:

```powershell
cd occt-autocad-project
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 -DOCCT_DIR="C:/path/to/occt" ..
cmake --build . --config Release
ctest -C Release --output-on-failure
```

## Configuration and Integrations

Because each subproject manages its own build configuration, dependency paths are set per subproject:

| Subproject | Configuration mechanism | Variables to set |
|---|---|---|
| `Sample01`, `Sample02` | Hardcoded paths in `CMakeLists.txt` | `Qt5_DIR`, `OCCT_INCLUDE_DIR`, `OCCT_LIB_DIR` |
| `Sample03` | Hardcoded paths in `CMakeLists.txt` (post-build step copies Coin3D/SoQt DLLs on MSVC) | `Qt5_DIR`, `OCCT_INCLUDE_DIR`, `OCCT_LIB_DIR`, `COIN3D_ROOT`, `SOQT_ROOT` |
| `occt-autocad-project` | CMake cache variable + `FetchContent` (`nlohmann/json` v3.11.2, `Catch2` v2.13.10) | `-DOCCT_DIR=<path-to-occt>` |

## Documentation

| Topic | What it covers | Link |
|---|---|---|
| Start with Sample01 | Feature list, environment requirements, and build steps for the minimal OCCT + Qt 5 sample | [Sample01/README.md](./Sample01/README.md) |
| Explore the CAD prototype | Overview, directory layout, and build notes for `occt-autocad-project` | [occt-autocad-project/README.md](./occt-autocad-project/README.md) |
| Study the CAD data model | `DBObject`, `Entity`, `Table`, `Database`, command transactions, and plugin extension design | [occt-autocad-project/docs/ARCHITECTURE.md](./occt-autocad-project/docs/ARCHITECTURE.md) |
| Follow coding conventions | Naming rules, C++17/Qt conventions, UI interaction specs, and module boundaries | [occt-autocad-project/docs/DEVELOPMENT_GUIDELINES.md](./occt-autocad-project/docs/DEVELOPMENT_GUIDELINES.md) |
| Contribute changes | Branching workflow, Conventional Commits style, formatting, and CTest checks | [occt-autocad-project/CONTRIBUTING.md](./occt-autocad-project/CONTRIBUTING.md) |

## Contributing

Contributions are welcome via GitHub issues and pull requests. For branch naming, Conventional Commits guidelines, `clang-format` usage, and CTest verification steps, see [occt-autocad-project/CONTRIBUTING.md](./occt-autocad-project/CONTRIBUTING.md).

## License

This repository is licensed under the GNU General Public License v3.0 (GPL-3.0). See [LICENSE](./LICENSE) for details.
