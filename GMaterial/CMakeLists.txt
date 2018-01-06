# CMake lowest version
cmake_minimum_required (VERSION 3.1)

set (CMAKE_CXX_STANDARD 11)

# 项目信息
project (GMaterialTest)
# 指定生成目标
add_executable(GMaterialTest GMaterial.cc)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(SQLite3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  target_link_libraries (GMaterialTest ${SQLITE3_LIBRARIES})
endif (SQLITE3_FOUND)

# include_directories(/usr/include)
# link_directories(/usr/lib)
