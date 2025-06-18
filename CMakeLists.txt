# cmake_minimum_required(VERSION 3.10.0)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# project(TcpServerLib VERSION 0.1.0 LANGUAGES C CXX)

# include_directories({CMAKE_SOURCE_DIR}/inc)

# add_library(TcpServerLib src/TcpServer.cpp)

# target_link_libraries(TcpServerLib PRIVATE Ws2_32)




cmake_minimum_required(VERSION 3.10)
project(TcpServerLib VERSION 1.0 LANGUAGES CXX)

# Define the library (STATIC for .lib, SHARED for .dll+.lib)
add_library(TcpServerLib STATIC
    src/TcpServer.cpp
)

# Specify include directories for the library
target_include_directories(TcpServerLib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
)

# Set properties for Windows export/import symbols
if(WIN32)
    target_compile_definitions(TcpServerLib PRIVATE TcpServerLib_EXPORTS)
    target_link_libraries(TcpServerLib PUBLIC Ws2_32)
endif()

# Specify C++ standard
target_compile_features(TcpServerLib PUBLIC cxx_std_17)

# Install the library and headers
install(TARGETS TcpServerLib
    EXPORT TcpServerLibTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY inc/ DESTINATION inc)

# Generate and install export information
install(EXPORT TcpServerLibTargets
    FILE TcpServerLibTargets.cmake
    NAMESPACE TcpServerLib::
    DESTINATION lib/cmake/TcpServerLib
)

# Create and install CMake package configuration
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/TcpServerLibConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/TcpServerLibConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/TcpServerLibConfigVersion.cmake"
    DESTINATION lib/cmake/TcpServerLib
)

# Optional: Generate a config file for find_package
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/TcpServerLibConfig.cmake"
    "include(\${CMAKE_CURRENT_LIST_DIR}/TcpServerLibTargets.cmake)"
)