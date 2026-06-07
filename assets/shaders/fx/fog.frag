#version 330 core
in vec2 v_uv;
in float v_depth;

uniform vec3 u_color;
uniform sampler2D u_texture;
uniform int u_use_texture;
uniform vec3 u_fog_color;
uniform float u_fog_near;
uniform float u_fog_far;

out vec4 frag_color;

void main() {
    vec3 base = u_use_texture == 1 ? texture(u_texture, v_uv).rgb * u_color : u_color;
    float fog_factor = clamp((u_fog_far + v_depth) / (u_fog_far - u_fog_near), 0.0, 1.0);
    frag_color = vec4(mix(u_fog_color, base, fog_factor), 1.0);
}
