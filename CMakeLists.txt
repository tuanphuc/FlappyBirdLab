cmake_minimum_required (VERSION 3.2)

project(FlappyBirdLab)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Be nice and export compile commands by default, this is handy for clang-tidy
# and for other tools.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# We can use include() and find_package() for our scripts in there
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

#configure directories
set (SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
# Set includes
include_directories("${PROJECT_SOURCE_DIR}/include")
# Set sources
file (GLOB SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_compile_options(-Wall -Wextra)
add_executable (${PROJECT_NAME} main.cpp ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} sfml-graphics)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin/)

include(cleanCppExtensions)
addMiscTargets()
