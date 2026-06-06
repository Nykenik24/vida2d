#version 330 core
in vec2 v_uv;

uniform vec3 u_color;
uniform float u_alpha;
uniform sampler2D u_texture;
uniform bool u_use_texture;

out vec4 frag_color;

void main() {
    vec4 base = u_use_texture ? texture(u_texture, v_uv) * vec4(u_color, u_alpha)
                              : vec4(u_color, u_alpha);
    frag_color = base;
}
