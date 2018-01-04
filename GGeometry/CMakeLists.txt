# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# 项目信息
project (GGeometryTest)
# 指定生成目标
add_executable(GGeometryTest GCuboid.cc GGeometryTest.cc)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_GEO)
# 生成链接库
add_library (GGometry ${DIR_LIB_GEO})

