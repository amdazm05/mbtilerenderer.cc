cmake_minimum_required(VERSION 3.12)
project(mbrenderer)
set(CMAKE_CXX_FLAGS "-std=c++20 -Wno-dev")
set(proto_path ${CMAKE_SOURCE_DIR}/third-party/vector-tile-spec/2.1/)
set(destination_dir  ${CMAKE_SOURCE_DIR}/proto/)
option(PROTO_COMPILE 0)
find_package(protobuf REQUIRED CONFIG)
include_directories(${protobuf_INCLUDE_DIR})
if(PROTO_COMPILE)
  execute_process(
      COMMAND protoc vector_tile.proto --proto_path=${proto_path} --cpp_out ${destination_dir}
      RESULT_VARIABLE result
  )
  if(result EQUAL 0)
      message(STATUS "Proto - Code generation completed successfully!")
  else()
      message(WARNING "PROTO - Code generation failed with error code: ${result}")
  endif()
endif()

include_directories(${CMAKE_SOURCE_DIR}/proto/)
add_subdirectory(${CMAKE_SOURCE_DIR}/third-party/SQLiteCpp)
file(COPY ${CMAKE_SOURCE_DIR}/sample 
DESTINATION ${CMAKE_BINARY_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/third-party/stb/
  ${CMAKE_SOURCE_DIR}/third-party/gzip-hpp/include/
  ${CMAKE_SOURCE_DIR}/include/
)
file(GLOB SRC_MB
${PROJECT_SOURCE_DIR}/proto/*.cc
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
target_link_libraries(mbrenderer 
  PUBLIC
  SQLiteCpp
  sqlite3
  pthread
  z
  protobuf::libprotobuf
)
add_executable(mbtiletest ${CMAKE_SOURCE_DIR}/test/mbtilesearchtiletest.cc)
target_link_libraries(mbtiletest
  PUBLIC
  mbrenderer
)

add_executable(decomtest ${CMAKE_SOURCE_DIR}/test/decompressortest.cc)
target_link_libraries(decomtest PUBLIC
  mbrenderer
)

add_executable(mbtilecachetest ${CMAKE_SOURCE_DIR}/test/mbtilecachertest.cc)
target_link_libraries(mbtilecachetest PUBLIC
  mbrenderer
)

add_executable(conversiontest ${CMAKE_SOURCE_DIR}/test/conversiontest.cc)
target_link_libraries(conversiontest PUBLIC
  mbrenderer
)

add_executable(vectortiletest ${CMAKE_SOURCE_DIR}/test/vectortiletest.cc)
target_link_libraries(vectortiletest PUBLIC
  mbrenderer
)
