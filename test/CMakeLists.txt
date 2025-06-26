link_libraries(type_map)

add_executable(type_map_test type_map.cpp)
add_test(NAME "type_map test" COMMAND type_map_test)

add_executable(iota_map_test iota_map.cpp)
add_test(NAME "iota_map test" COMMAND iota_map_test)