#version 330 core
in vec2 v_uv;

uniform vec3 u_color;
uniform float u_time;
uniform sampler2D u_texture;
uniform bool u_use_texture;
uniform float u_dissolve_speed;

out vec4 frag_color;

float noise(vec2 p) {
    return fract(sin(dot(p, vec2(127.1, 311.7))) * 43758.5453);
}

void main() {
    vec3 base = u_use_texture ? texture(u_texture, v_uv).rgb * u_color
                              : u_color;
    float n = noise(v_uv);
    float threshold = fract(u_time * u_dissolve_speed);
    if (n < threshold) discard;
    frag_color = vec4(base, 1.0);
}
