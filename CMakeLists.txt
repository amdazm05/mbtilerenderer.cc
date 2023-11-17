cmake_minimum_required(VERSION 3.12)
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
add_executable(mbtiletest ${CMAKE_SOURCE_DIR}/test/mbtiletest.cc)
target_link_libraries(mbtiletest
  SQLiteCpp
  sqlite3
  pthread
  mbrenderer
)

