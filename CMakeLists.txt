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
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(bin_dir ${CMAKE_BINARY_DIR}/bin)
make_directory(${CMAKE_BINARY_DIR}/data)
file(COPY ${PROJECT_SOURCE_DIR}/data/${source_csv} DESTINATION ${CMAKE_BINARY_DIR}/data)
make_directory(${CMAKE_BINARY_DIR}/output)

include(src/CMakeLists.txt)

################################
# googleTest
################################
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/master.zip
)
enable_testing()
include_directories(gtest/include)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

################################
# Unit Tests
################################
add_executable(ngram_test test/ngram_test.cpp)
target_link_libraries(ngram_test gtest gtest_main ${project_name}.so)

include(GoogleTest)
gtest_discover_tests(ngram_test)