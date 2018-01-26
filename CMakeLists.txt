# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

# Pronect name
project (GSimTestRun)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_SRCS 变量
aux_source_directory(. DIR_SRCS)

# 添加子目录
add_subdirectory(GEvent)
add_subdirectory(GGeometry)
# add_subdirectory(GRand)
add_subdirectory(GSimProcess)
add_subdirectory(GSource)
add_subdirectory(GSpectra)


# Debug mode
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# 指定生成目标
add_executable(GSimTestRun SimTestRun.cc)

# Add links
# Note many link files were moved down to GSimProcess folder.
# target_link_libraries(GSimTestRun GSimProcess GRand GEvent GGometry GSource)
# target_link_libraries(GSimTestRun GGometry GSource GSpectra GSimProcess GEvent)
target_link_libraries(GSimTestRun GEvent GSimProcess)

#Note: To compile with debug mode use:
#	cmake -DCMAKE_BUILD_TYPE=Debug ..
