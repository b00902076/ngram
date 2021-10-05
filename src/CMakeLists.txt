set(lib_list "")
set(components_dir ${CMAKE_CURRENT_LIST_DIR}/components)
set(config_dir ${CMAKE_CURRENT_LIST_DIR}/config)
get_all_cpps(components ${components_dir})
get_all_cpps(config ${config_dir})
list(APPEND lib_list ${components})
list(APPEND lib_list ${config})
add_library(${project_name}.so SHARED ${lib_list})

# print_list(lib_list)

add_custom_target(run
    COMMAND ${project_name}
    DEPENDS ${project_name}
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
add_executable(${project_name} ${CMAKE_CURRENT_LIST_DIR}/main.cpp)
target_link_libraries(${project_name} ${project_name}.so)
