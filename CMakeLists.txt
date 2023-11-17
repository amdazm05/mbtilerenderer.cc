cmake_minimum_required(VERSION 3.12)
set(CXX_STANDARD 20)
project(mbrenderer)
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/SQLiteCpp)
file(COPY ${CMAKE_SOURCE_DIR}/sample 
DESTINATION ${CMAKE_BINARY_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/third-party/stb/
  ${CMAKE_SOURCE_DIR}/third-party/gzip-hpp/include/
)
file(GLOB SRC_MB
${PROJECT_SOURCE_DIR}/src/*.cpp
${PROJECT_SOURCE_DIR}/src/*.cc
${PROJECT_SOURCE_DIR}/src/util/*.cpp
${PROJECT_SOURCE_DIR}/src/util/*.cc
)

message("${SRC_MB}")
add_library(mbrenderer STATIC ${SRC_MB}
)

target_include_directories(mbrenderer PUBLIC
  ${CMAKE_SOURCE_DIR}/include/
)
add_executable(mbtiletest ${CMAKE_SOURCE_DIR}/test/mbtilesearchtiletest.cc)
target_link_libraries(mbtiletest
  SQLiteCpp
  sqlite3
  pthread
  z
  mbrenderer
)

add_executable(decomtest ${CMAKE_SOURCE_DIR}/test/decompressortest.cc)
target_link_libraries(decomtest
  SQLiteCpp
  sqlite3
  pthread
  z
  mbrenderer
)


