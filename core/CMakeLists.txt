file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(vida_core STATIC ${SOURCES})
add_library(vida::core ALIAS vida_core)

set_target_properties(vida_core PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/vida
)

target_include_directories(vida_core
    PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_options(vida_core PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
)

target_link_libraries(vida_core PUBLIC glm::glm)
