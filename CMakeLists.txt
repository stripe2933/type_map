cmake_minimum_required(VERSION 3.28)

# Enable experimental standard library module support.
if (CMAKE_VERSION VERSION_GREATER_EQUAL "4.0")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "a9e1cf81-9932-4810-974b-6eccaf14e457")
elseif (CMAKE_VERSION VERSION_GREATER_EQUAL "3.30")
    set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
endif()

project(type_map
    LANGUAGES CXX
    VERSION 0.1.0
    DESCRIPTION "Convert runtime values to compile-time types."
)

# ----- CMake Options -----

option(TYPE_MAP_USE_STD_MODULE "Use standard library module" ON)
option(TYPE_MAP_TEST "Enable test targets" OFF)

# ----- type_map -----

add_library(type_map)
target_sources(type_map PUBLIC
    FILE_SET CXX_MODULES
    FILES type_map.cppm
)
target_compile_features(type_map PUBLIC cxx_std_23)

add_library(type_map::type_map ALIAS type_map)

if (TYPE_MAP_USE_STD_MODULE)
    # Enable standard library module feature for type_map CMake target.
    cmake_minimum_required(VERSION 3.30)
    set_target_properties(type_map PROPERTIES CXX_MODULE_STD 1)
endif()

# ----- Tests -----

if (TYPE_MAP_TEST)
    enable_testing()
    add_subdirectory(test)
endif()

# ----- Packaging -----

include(GNUInstallDirs)
install(
    TARGETS type_map
    EXPORT "${PROJECT_NAME}Targets"
    FILE_SET CXX_MODULES DESTINATION module/${PROJECT_NAME}
)
install(
    EXPORT "${PROJECT_NAME}Targets"
    DESTINATION cmake/${PROJECT_NAME}
    NAMESPACE ${PROJECT_NAME}::
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)
configure_package_config_file(
    cmake/config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION cmake/${PROJECT_NAME}
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION cmake/${PROJECT_NAME}
)