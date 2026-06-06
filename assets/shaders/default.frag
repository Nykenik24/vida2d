#version 330 core
in vec2 v_uv;
in vec3 v_normal;

uniform vec3 u_color;

out vec4 frag_color;

void main() {
    frag_color = vec4(u_color, 1.0);
}
