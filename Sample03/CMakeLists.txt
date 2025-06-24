cmake_minimum_required(VERSION 3.16)
project(Sample03 LANGUAGES CXX)

# 启用Unity Build (CMake 3.16+)
set(CMAKE_UNITY_BUILD ON)  # 可选：设置整个项目启用Unity Build
set(CMAKE_UNITY_BUILD_BATCH_SIZE 8)  # 每个统一文件包含的源文件数

# 设置并行编译
if(MSVC)
    add_compile_options(/MP)  # MSVC的并行编译选项
endif()

if (MSVC)
    add_compile_options(/utf-8)
endif()

# 全局配置
set(CMAKE_CXX_STANDARD 17) # OCCT需要C++14/17，提升版本
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 强制使用指定标准
set(CMAKE_AUTOMOC ON) # 必须启用：自动处理Qt的moc
set(CMAKE_AUTORCC ON) # 自动处理资源文件
set(CMAKE_AUTOUIC ON) # 自动处理UI文件
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # 包含当前目录

# 设置Qt和OCCT路径
set(Qt5_DIR "D:/tools/QT/5.14.2/msvc2017_64/lib/cmake/Qt5")
set(OCCT_INCLUDE_DIR "D:/tools/occt-vc144-64/inc")
set(OCCT_LIB_DIR "D:/tools/occt-vc144-64/win64/vc14/lib")

# 查找Qt组件
find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

# 定义OCCT核心库
set(OCCT_LIBS
    TKernel
    TKMath
    TKG2d
    TKG3d
    TKBRep
    TKGeomBase
    TKGeomAlgo
    TKHLR
    TKFillet
    TKOffset
    TKFeat
    TKStd
    TKTopAlgo
    TKService
    TKV3d
    TKOpenGl
    TKMesh
    TKShHealing
    TKPrim
    TKBO
    TKBool
    TKCAF
    TKCDF
    TKXCAF
    TKXSBase
    TKLCAF
    TKBinL
    TKXmlL
    TKBin
    TKXml
)

# 添加源文件
set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/core/Viewport.cpp
    src/core/ViewportManager.cpp
    src/actions/Action.cpp
    src/actions/ActionManager.cpp
    src/actions/ActionFactory.cpp
    src/actions/DisplayModeAction.cpp
    src/actions/CreateShapeAction.cpp
    src/actions/RandomTestAction.cpp
    src/config/UIConfig.cpp
    src/core/SimpleEntity.cpp
    src/core/EntityFactory.cpp
    src/entities/BoxEntity.cpp
    src/entities/CylinderEntity.cpp
    src/entities/FrustumEntity.cpp
    src/entities/TorusEntity.cpp
    src/entities/SphereEntity.cpp
    src/actions/FileAction.cpp
    src/actions/ClearAction.cpp
)

# 添加头文件
set(HEADERS
    src/MainWindow.h
    src/core/Viewport.h
    src/core/ViewportManager.h
    src/actions/Action.h
    src/actions/ActionManager.h
    src/actions/ActionFactory.h
    src/actions/DisplayModeAction.h
    src/actions/CreateShapeAction.h
    src/actions/RandomTestAction.h
    src/config/UIConfig.h
    src/core/SimpleEntity.h
    src/core/EntityFactory.h
    src/entities/BoxEntity.h
    src/entities/CylinderEntity.h
    src/entities/FrustumEntity.h
    src/entities/TorusEntity.h
    src/entities/SphereEntity.h
    src/actions/FileAction.h
    src/actions/ClearAction.h
)

# 添加资源文件
set(RESOURCES
    resources/resources.qrc
)

# 创建可执行文件
add_executable(${PROJECT_NAME} 
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# 包含目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${OCCT_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# 指定库搜索路径
target_link_directories(${PROJECT_NAME} PRIVATE
    ${OCCT_LIB_DIR}
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    ${OCCT_LIBS}
)

# 设置C++标准
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# 安装目标
install(TARGETS ${PROJECT_NAME} DESTINATION bin) 