cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

include(cmake/macros.cmake)

set(project_name ngram)
project(${project_name} CXX)
set(source_csv KEN_ALL.CSV)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
make_directory(${CMAKE_BINARY_DIR}/data)
file(COPY ${PROJECT_SOURCE_DIR}/data/${source_csv} DESTINATION ${CMAKE_BINARY_DIR}/data)
make_directory(${CMAKE_BINARY_DIR}/output)

include(src/CMakeLists.txt)