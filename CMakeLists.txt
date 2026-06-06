cmake_minimum_required(VERSION 4.3)
project(vida VERSION 0.1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_library(glad STATIC vendored/glad/src/glad.c)
target_include_directories(glad PUBLIC vendored/glad/include)

add_subdirectory(vendored/glfw EXCLUDE_FROM_ALL)
add_subdirectory(vendored/glm EXCLUDE_FROM_ALL)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_subdirectory(core)

file(GLOB COMPONENT_DIRS CONFIGURE_DEPENDS components/*)

foreach(COMPONENT_DIR ${COMPONENT_DIRS})
  if(IS_DIRECTORY ${COMPONENT_DIR} AND EXISTS ${COMPONENT_DIR}/CMakeLists.txt)
    message(STATUS "vida: found component → ${COMPONENT_DIR}")
    add_subdirectory(${COMPONENT_DIR})
  endif()
endforeach()

file(GLOB EXAMPLE_DIRS CONFIGURE_DEPENDS examples/*)

foreach(EXAMPLE_DIR ${EXAMPLE_DIRS})
  if(IS_DIRECTORY ${EXAMPLE_DIR} AND EXISTS ${EXAMPLE_DIR}/CMakeLists.txt)
    message(STATUS "vida: found example → ${EXAMPLE_DIR}")
    add_subdirectory(${EXAMPLE_DIR})
  endif()
endforeach()
