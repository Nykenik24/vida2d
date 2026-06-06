add_executable(basic main.cpp)

target_link_libraries(basic PRIVATE
    vida::core
    vida::renderer2d
    vida::input
)

set_target_properties(basic PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

if(UNIX AND NOT APPLE)
  target_link_libraries(basic PRIVATE m dl pthread)
endif()
