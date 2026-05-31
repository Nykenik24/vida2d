cmake_minimum_required(VERSION 4.3)

project(vida2d
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(SDL_SHARED        OFF CACHE BOOL "" FORCE)
set(SDL_STATIC        ON  CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY  OFF CACHE BOOL "" FORCE)
set(SDL_TESTS         OFF CACHE BOOL "" FORCE)
set(SDL_INSTALL_TESTS OFF CACHE BOOL "" FORCE)

add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

set(SDLTTF_VENDORED       ON  CACHE BOOL "" FORCE)
set(SDLTTF_SAMPLES        OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS     OFF CACHE BOOL "" FORCE)
add_subdirectory(vendored/SDL_ttf EXCLUDE_FROM_ALL)

file(GLOB_RECURSE VIDA2D_SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_library(vida2d STATIC ${VIDA2D_SOURCES})

target_include_directories(vida2d
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vida2d
    PUBLIC SDL3-static SDL3_ttf-static
)

target_compile_options(vida2d PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

set_target_properties(vida2d PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

file(GLOB EXAMPLE_SOURCES CONFIGURE_DEPENDS examples/*.cpp)

foreach(EXAMPLE_SRC ${EXAMPLE_SOURCES})
  get_filename_component(EXAMPLE_NAME ${EXAMPLE_SRC} NAME_WE)

  add_executable(${EXAMPLE_NAME} ${EXAMPLE_SRC})

  target_link_libraries(${EXAMPLE_NAME} PRIVATE vida2d)

  if(UNIX AND NOT APPLE)
    target_link_libraries(${EXAMPLE_NAME} PRIVATE m dl pthread)
  endif()

  set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
  )
endforeach()
