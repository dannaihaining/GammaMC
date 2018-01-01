# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# 项目信息
project (GGeometryTest)
# 指定生成目标
add_executable(GGeometryTest GCuboid.cc GGeometryTest.cc)

