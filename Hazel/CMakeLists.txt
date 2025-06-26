cmake_minimum_required(VERSION 3.15)
project(Hazel LANGUAGES CXX)

# 1. 设置动态库选项
option(Hazel_SHARED "Build Hazel as a shared library (DLL)" ON)

# 收集所有源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/Hazel/*.cpp"
)

# 创建库目标
add_library(Hazel SHARED ${SOURCES})

# MSVC: 强制使用 UTF-8 编码
target_compile_options(Hazel PRIVATE "$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# Windows平台特定设置
if(WIN32)
    target_compile_definitions(Hazel PUBLIC HZ_PLATFORM_WINDOWS)
	message("current platform: Windows ")
elseif(UNIX)
    target_compile_definitions(Hazel PUBLIC HZ_PLATFORM_LINUX)
	message("current platform: Linux ")
endif()

# 关键的头文件包含路径设置
target_include_directories(Hazel PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>  # 为了找到Hazel.h
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Hazel>  # 为了找到Hazel/子目录下的头文件
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog/include>
    $<INSTALL_INTERFACE:include>
)

# DLL导出定义
target_compile_definitions(Hazel PRIVATE HAZEL_BUILD_DLL)

# 输出路径设置
set_target_properties(Hazel PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Sandbox/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Sandbox/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/Sandbox/lib
)