#version 330 core
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec2 a_uv;
layout(location = 2) in vec3 a_normal;

uniform mat4 u_mvp;
uniform mat4 u_model;

out vec2 v_uv;
out float v_depth;

void main() {
    vec4 world_pos = u_model * vec4(a_pos, 1.0);
    gl_Position    = u_mvp * vec4(a_pos, 1.0);
    v_uv           = a_uv;
    v_depth        = world_pos.z;
}
