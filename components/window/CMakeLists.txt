file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(vida_window STATIC ${SOURCES})
add_library(vida::window ALIAS vida_window)

set_target_properties(vida_window PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/vida
)

target_include_directories(vida_window
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vida_window
    PUBLIC
        vida::core
        glfw
        OpenGL::GL
        glad
)

target_compile_options(vida_window PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
