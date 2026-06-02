cmake_minimum_required(VERSION 4.3)

project(vida
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "" FORCE)
set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendored/freeglut EXCLUDE_FROM_ALL)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE VIDA2D_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(vida STATIC ${VIDA2D_SOURCES})

target_include_directories(vida
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vida
    PUBLIC
        OpenGL::GL
        freeglut_static
)

target_compile_definitions(vida PUBLIC FREEGLUT_STATIC)

target_compile_options(vida PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS examples/*.cpp)

foreach(EXAMPLE_SRC ${EXAMPLE_SOURCES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})
  target_link_libraries(${EXAMPLE_NAME} PRIVATE vida)

  set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
    )

  if(UNIX AND NOT APPLE)
    target_link_libraries(${EXAMPLE_NAME} PRIVATE m dl pthread)
  endif()
endforeach()
