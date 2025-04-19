cmake_minimum_required(VERSION 3.16)
project(JXCqmlTools VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)  # 启用 CMake 的自动 MOC（元对象编译器）支持
set(CMAKE_AUTORCC ON)  # 启用 CMake 的自动资源文件编译支持
set(CMAKE_CXX_STANDARD 17)  # 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 确保使用 C++17 标准，不使用更低版本
set(CMAKE_INCLUDE_CURRENT_DIR ON)  # 自动将当前目录包含到编译器的头文件搜索路径中

# 版本相关信息
set(GIT_TAG_WITH_COMMA "1,0,0,0")  # 示例版本号
set(GIT_COMMIT_COUNT "0")        # 示例提交计数
set(GIT_SEMVER "1.0.0")            # 示例语义化版本‘
set(PROJECT_DESCRIPTION "JXC Project Description")  # 项目描述
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # 设置可执行文件输出目录


message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

# 设置 QML 文件列表
# 这些文件将在项目中作为 QML 资源被使用
set(QML_FILES
    qml/App.qml    # 主应用的 QML 文件
    qml/MainWindow.qml  # 主窗口的 QML 文件
    qml/global/ItemsOriginal.qml # 全局数据模型
    qml/global/GlobalModel.qml  # 全局模型
    qml/global/ItemsFooter.qml # 底部导航栏数据模型
    qml/page/Xiaoju_Jiaoliu_Config.qml # 小桔 交流桩 配置页面
)

# 设置源文件列表
# 这些是项目的源代码文件，将用于构建可执行文件
set(SOURCE_FILES
    src/main.cpp    # 项目的入口文件
)

# 设置资源文件列表
# 目前没有添加任何资源文件
set(RESOURCES_FILES
    res.qrc
)

# 查找 Qt6 库（版本 6.2 及以上），并确保 QtQuick 模块被找到
# 添加QtSql模块
find_package(Qt6 6.2 COMPONENTS Quick REQUIRED SerialPort Widgets Sql REQUIRED)
# 关于QXlsx
add_subdirectory(QXlsx)

# 使用 qt_add_executable 创建 Qt 应用程序
# 使用指定的源文件生成可执行文件
qt_add_executable(${PROJECT_NAME}
    ${SOURCE_FILES}    # 添加主应用程序源文件
)

# 使用 qt_add_qml_module 配置 QML 模块
# 此模块将 QML 文件组织成一个模块，使其能够在应用中引用
qt_add_qml_module(${PROJECT_NAME}
    URI JXCqmlTools         # QML 模块的 URI（统一资源标识符）
    VERSION 1.0             # QML 模块的版本号
    RESOURCE_PREFIX /qt/qml  # QML 文件在资源中的前缀路径
    RESOURCES ${RESOURCES_FILES}  # 指定资源文件列表
    QML_FILES ${QML_FILES}
    SOURCES src/main.cpp
    RESOURCES res.qrc
    RESOURCES qml/global/qmldir
    SOURCES src/handler/ButtonHandler.h src/main.cpp
    SOURCES src/handler/ButtonHandler.cpp
    SOURCES src/include/serial_config.h
    SOURCES src/handler/DeviceSnHandler.h
    SOURCES src/handler/DeviceSnHandler.cpp
    QML_FILES qml/page/NWwdx_Jiaoliu_Config.qml
    QML_FILES qml/page/HC_Excel_Census.qml
    SOURCES src/models/Station.cpp src/models/Station.h
    SOURCES src/models/Station.cpp src/models/Station.h
    SOURCES src/handler/HcHandler.h
    SOURCES src/handler/HcHandler.cpp
    QML_FILES qml/page/CurveAnalysisTool.qml
    SOURCES src/models/OpenGLRenderer.h
    SOURCES src/models/OpenGLRenderer.cpp
    SOURCES src/models/OpenGLItem.h
)


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(${PROJECT_NAME} PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# 将当前项目的 src 目录添加到编译器的头文件搜索路径中
# 这意味着项目中的源文件可以引用 src 目录中的头文件
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src   # 使用相对路径指定 src 目录
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Core Qt6::Quick Qt6::SerialPort Qt6::Widgets Qt6::Sql
)

# 关于QXlsx
target_link_libraries(${PROJECT_NAME} PRIVATE QXlsx::QXlsx)


include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})


# win32
#复制程序运行所需要的动态库
if (WIN32)
    if (MSVC)
        if (CMAKE_SIZEOF_VOID_P EQUAL 4)
            file(GLOB_RECURSE 3RDPARTY_DLL_DIR ${CMAKE_SOURCE_DIR}/3rdparty/msvc/x86/*.dll)
        elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
            file(GLOB_RECURSE 3RDPARTY_DLL_DIR ${CMAKE_SOURCE_DIR}/3rdparty/msvc/x64/*.dll)
        endif ()
    elseif (MINGW)
        file(GLOB_RECURSE 3RDPARTY_DLL_DIR ${CMAKE_SOURCE_DIR}/3rdparty/mingw/*.dll)
    endif ()
    file(COPY ${3RDPARTY_DLL_DIR} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif ()

# 生成版本信息头文件
set(HEADER_FILE_VERSION_PATH ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/Version.h)
configure_file(
        ${CMAKE_SOURCE_DIR}/.cmake/Version.h.in
        ${HEADER_FILE_VERSION_PATH}
)

# 如果是Windows平台，则生成rc文件，还有inno setup脚本文件
set(EXAMPLE_VERSION_RC_PATH "")
if (WIN32)
    set(EXAMPLE_VERSION_RC_PATH ${CMAKE_CURRENT_BINARY_DIR}/version_${PROJECT_NAME}.rc)
    configure_file(
        ${CMAKE_SOURCE_DIR}/.cmake/version_exe.rc.in
        ${EXAMPLE_VERSION_RC_PATH}
        # @ONLY
    )
    target_sources(${PROJECT_NAME} PRIVATE ${EXAMPLE_VERSION_RC_PATH})
    configure_file(
        ${CMAKE_SOURCE_DIR}/.cmake/InstallerScript.iss.in
        ${CMAKE_SOURCE_DIR}/package/InstallerScript.iss
    )
endif ()


#添加部署脚本
if (CMAKE_BUILD_TYPE MATCHES "Release")
    if (APPLE)
        find_program(QT_DEPLOY_QT NAMES macdeployqt)
        add_custom_target(Script-DeployRelease
                COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/dist
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_SOURCE_DIR}/dist
                COMMAND ${QT_DEPLOY_QT} ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}.app -qmldir=${CMAKE_SOURCE_DIR}
                COMMENT "MacOs Deploying Qt Dependencies After Build........."
                SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()
    if (WIN32)
        find_program(QT_DEPLOY_QT NAMES windeployqt)
        add_custom_target(Script-DeployRelease
                COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/dist
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ${CMAKE_SOURCE_DIR}/dist
                COMMAND ${QT_DEPLOY_QT} --qmldir=${CMAKE_CURRENT_LIST_DIR} --plugindir ${CMAKE_SOURCE_DIR}/dist/plugins --no-translations --compiler-runtime ${CMAKE_SOURCE_DIR}/dist/${PROJECT_NAME}.exe
                COMMENT "Windows Deploying Qt Dependencies After Build........."
                SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        )
    endif ()
endif ()
