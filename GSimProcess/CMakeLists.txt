# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# 查找当前目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(. DIR_LIB_SIM)
# 生成链接库
add_library (GSimProcess ${DIR_LIB_SIM})


target_link_libraries(GSimProcess GGometry GSource GSpectra GEvent)
