file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(vida_renderer3d STATIC ${SOURCES})
add_library(vida::renderer3d ALIAS vida_renderer3d)

set_target_properties(vida_renderer3d PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/vida
)

target_include_directories(vida_renderer3d
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(vida_renderer3d
    PUBLIC
        vida::core
        vida::window
        glfw
        OpenGL::GL
)

target_compile_definitions(vida_renderer3d PUBLIC FREEGLUT_STATIC)

target_compile_options(vida_renderer3d PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)
