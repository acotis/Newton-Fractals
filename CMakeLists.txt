cmake_minimum_required(VERSION 3.7)
project(NewtonFractals)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/evan/Programs/C++/CLionProjects/NewtonFractals/cmake-build-debug")

set(SOURCE_FILES src/main.cpp src/Constants.h src/NewtonFractal.cpp src/NewtonFractal.h src/Typedefs.h src/gui/Button.cpp src/gui/Button.h src/gui/FractalCanvas.cpp src/gui/FractalCanvas.h src/gui/ClickablePanel.cpp src/gui/ClickablePanel.h src/gui/Clickable.h src/gui/ResolutionPicker.cpp src/gui/ResolutionPicker.h)
add_executable(NewtonFractals ${SOURCE_FILES})

# Threads package
find_package(Threads REQUIRED)

# PNG++ package
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(NewtonFractals ${PNG_LIBRARY})

# Tell cmake where to find the SFML-finding script
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-modules")
# Use the script to find SFML
find_package(SFML COMPONENTS window graphics system network audio REQUIRED)
# Include the directories (not entirely sure what that means)
include_directories(${SFML_INCLUDE_DIR})
# Link my project to the found libraries
target_link_libraries(NewtonFractals ${SFML_LIBRARIES} Threads::Threads)


