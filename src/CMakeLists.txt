set(lib_list "")
get_all_cpps(lib_ngram ${PROJECT_SOURCE_DIR}/lib/ngram)
get_all_cpps(indexer ${PROJECT_SOURCE_DIR}/src/indexer)
get_all_cpps(searcher ${PROJECT_SOURCE_DIR}/src/searcher)
list(APPEND lib_list ${lib_ngram})
list(APPEND lib_list ${indexer})
list(APPEND lib_list ${searcher})
add_library(${project_name}.so SHARED ${lib_list})

# print_list(lib_list)

add_custom_target(run
    COMMAND ${project_name}
    DEPENDS ${project_name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_executable(${project_name} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_link_libraries(${project_name} ${project_name}.so)
