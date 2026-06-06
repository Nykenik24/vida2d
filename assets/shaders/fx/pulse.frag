#version 330 core
in vec2 v_uv;

uniform vec3 u_color;
uniform float u_time;
uniform sampler2D u_texture;
uniform bool u_use_texture;
uniform float u_pulse_speed;

out vec4 frag_color;

void main() {
    vec3 base = u_use_texture ? texture(u_texture, v_uv).rgb * u_color
                              : u_color;

    float pulse = 0.5 + 0.5 * sin(u_time * u_pulse_speed);
    frag_color = vec4(base * pulse, 1.0);
}
