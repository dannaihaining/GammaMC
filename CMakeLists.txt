# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# Pronect name
project (GSimTestRun)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加子目录
# add_subdirectory(GEvent)
add_subdirectory(GGeometry)
# add_subdirectory(GRand)
# add_subdirectory(GSimProcess)
add_subdirectory(GSource)
add_subdirectory(GSpectra)

# 指定生成目标
add_executable(GSimTestRun SimTestRun.cc)

# 添加链接库
# target_link_libraries(GSimTestRun GSimProcess GRand GEvent GGometry GSource)
target_link_libraries(GSimTestRun GGometry GSource GSpectra)

