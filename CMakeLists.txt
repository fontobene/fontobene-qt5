# CMake version configuration
cmake_minimum_required(VERSION 3.5...3.19)
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Define project
project(fontobene_qt5
    VERSION 0.1.0
    LANGUAGES CXX
)

# Options
option(FONTOBENE_ENABLE_TESTS "Build tests for fontobene-qt5." ON)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find required Qt packages
find_package(Qt5 5.2.0 COMPONENTS Core REQUIRED)

# Include subprojects
add_subdirectory(fontobene-qt5)
if(FONTOBENE_ENABLE_TESTS)
    add_subdirectory(tests)
endif()
