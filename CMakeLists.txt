cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")
include(cmake/macros.cmake)

# ###############################
# ngram
# ###############################

set(project_name ngram)
project(${project_name} CXX)
set(source_csv KEN_ALL.CSV)
set(query_filename queries)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
make_directory(${CMAKE_BINARY_DIR}/data)
file(COPY ${PROJECT_SOURCE_DIR}/data/${source_csv} DESTINATION ${CMAKE_BINARY_DIR}/data)
file(COPY ${PROJECT_SOURCE_DIR}/data/${query_filename} DESTINATION ${CMAKE_BINARY_DIR}/data)
make_directory(${CMAKE_BINARY_DIR}/output)
include_directories(include)

include(src/CMakeLists.txt)

################################
# googleTest
################################

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
enable_testing()
include_directories(gtest/include)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# requires CMake 3.14+
FetchContent_MakeAvailable(googletest)

################################
# Unit Tests
################################

include_directories(test/include)
file(COPY ${PROJECT_SOURCE_DIR}/data/${source_csv} DESTINATION ${CMAKE_BINARY_DIR}/test/data)
file(COPY ${PROJECT_SOURCE_DIR}/data/${query_filename} DESTINATION ${CMAKE_BINARY_DIR}/test/data)
file(COPY ${PROJECT_SOURCE_DIR}/test/data DESTINATION ${CMAKE_BINARY_DIR}/test)
make_directory(${CMAKE_BINARY_DIR}/test/output)
make_directory(${CMAKE_BINARY_DIR}/test/test_results)
make_directory(${CMAKE_BINARY_DIR}/test/test_results/linux)
make_directory(${CMAKE_BINARY_DIR}/test/test_results/windows)
make_directory(${CMAKE_BINARY_DIR}/test/test_results/unknown)
add_executable(ngram_test test/main.cpp)
target_link_libraries(ngram_test gtest gtest_main ${project_name}.so)

include(GoogleTest)
gtest_discover_tests(ngram_test)