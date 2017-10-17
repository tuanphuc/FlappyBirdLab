cmake_minimum_required (VERSION 3.2)

project(FlappyBirdLab)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")
# General compiler options
if (SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
endif()
# Add directory containing FindSFML.cmake to module path
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_MODULE_PATH}")
# Find SFML
# Note: SFML_STATIC_LIBRARIES determines which libraries are found by find_package()
find_package(SFML 2 COMPONENTS graphics window system)
# If found, include and link; otherwise output error message
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
else()
	set(SFML_ROOT "" CACHE PATH "SFML top-level directory")
	message("\n-> SFML directory not found. Set SFML_ROOT to SFML's top-level path (containing \"include\" and \"lib\" directories).")
	message("-> Make sure the SFML libraries with the same configuration (Release/Debug, Static/Dynamic) exist.\n")
endif()

#configure directories
set (SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
# Set includes
include_directories("${PROJECT_SOURCE_DIR}/include")
# Set sources
file (GLOB SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_compile_options(-Wall -Wextra)
add_executable (${PROJECT_NAME} main.cpp ${SOURCE_FILES})

# Build static or shared libraries? Set chapter-specific DLL import macro
if(SFML_STATIC_LIBRARIES)
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
endif()
# Link SFML. For versions < 2.2, SFML_DEPENDENCIES is not defined, and we do not need to link dependencies
if(SFML_VERSION_MINOR LESS 2)
      set(SFML_DEPENDENCIES "")
endif()
target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

install(DIRECTORY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/bin/)
