#version 330 core
in vec2 v_uv;

uniform vec3 u_color;
uniform float u_alpha;
uniform sampler2D u_texture;
uniform int u_use_texture;

out vec4 frag_color;

void main() {
    if (u_use_texture == 1)
        frag_color = texture(u_texture, v_uv) * vec4(u_color, u_alpha);
    else
        frag_color = vec4(u_color, u_alpha);
}
