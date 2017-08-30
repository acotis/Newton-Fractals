cmake_minimum_required(VERSION 3.7)
project(NewtonFractals)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/evan/Programs/C++/CLionProjects/NewtonFractals/cmake-build-debug")

set(SOURCE_FILES src/main.cpp src/NewtonFractal.cpp src/NewtonFractal.h src/Typedefs.h)
add_executable(NewtonFractals ${SOURCE_FILES})

# Threads package
find_package(Threads REQUIRED)

# Tell cmake where to find the SFML-finding script
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
# Use the script to find SFML
find_package(SFML COMPONENTS window graphics system network audio REQUIRED)
# Include the directories (not entirely sure what that means)
include_directories(${SFML_INCLUDE_DIR})
# Link my project to the found libraries
target_link_libraries(NewtonFractals ${SFML_LIBRARIES} Threads::Threads)


