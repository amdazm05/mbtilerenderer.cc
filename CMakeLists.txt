cmake_minimum_required(VERSION 3.12)
project(mbrenderer)
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/SQLiteCpp)
file(COPY ${CMAKE_SOURCE_DIR}/sample 
     DESTINATION ${CMAKE_BINARY_DIR})
include_directories(
    ${CMAKE_SOURCE_DIR}/third-party/stb
    ${CMAKE_SOURCE_DIR}/include/
)
add_executable(mbtiletest ${CMAKE_SOURCE_DIR}/test/mbtiletest.cc)
target_link_libraries(mbtiletest
  SQLiteCpp
  sqlite3
  pthread
)