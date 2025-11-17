# OCCT AutoCAD Project

## Overview
The OCCT AutoCAD Project is a CAD application built using the Open CASCADE Technology (OCCT) framework. This project aims to provide a robust platform for CAD functionalities similar to AutoCAD, enabling users to create, edit, and manage 2D and 3D geometries.

## Features
- **Document Management**: Efficient handling of CAD documents.
- **User Interface**: Intuitive UI for seamless interaction.
- **Geometry Creation**: Tools for creating and manipulating geometric shapes.
- **File I/O**: Support for reading and writing DXF and STEP files.
- **Plugin Architecture**: Extendable architecture for additional functionalities.

## Project Structure
- **CMakeLists.txt**: Build configuration file for CMake.
- **README.md**: Documentation and usage instructions.
- **LICENSE**: License information for the project.
- **.gitignore**: Specifies files and directories to ignore in version control.
- **.vscode/launch.json**: Debug configuration for VS Code.
- **cmake/FindOCCT.cmake**: CMake module for locating the OCCT library.
- **src/**: Contains the source code for the application.
- **include/**: Header files for the OCCT AutoCAD API.
- **examples/**: Example programs demonstrating project usage.
- **tools/**: Scripts for various utilities, including code generation.
- **tests/**: Unit tests for the application components.
- **third_party/**: Information about third-party libraries used in the project.

## Getting Started
1. **Clone the Repository**: 
   ```
   git clone <repository-url>
   cd occt-autocad-project
   ```

2. **Build the Project**:
   ```
   mkdir build
   cd build
   cmake ..
   make
   ```

3. **Run the Application**:
   ```
   ./occt-autocad-project
   ```

## Contributing
Contributions are welcome! Please submit a pull request or open an issue for any enhancements or bug fixes.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.