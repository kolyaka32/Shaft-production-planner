# Setting minimum required for cmake versions
cmake_minimum_required(VERSION 3.5)

# 
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)

# Creating project
project(Testing-app)

# Add all source files (that needed) under the src directory
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.rc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Find SFML packages
find_package(SFML 3.0.1 COMPONENTS System Window Graphics Audio REQUIRED)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio)
