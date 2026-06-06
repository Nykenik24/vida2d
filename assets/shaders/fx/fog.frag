#version 330 core
in vec2 v_uv;
in float v_depth;

uniform vec3 u_color;
uniform sampler2D u_texture;
uniform bool u_use_texture;

uniform vec3  u_fog_color = vec3(0.5, 0.5, 0.5);
uniform float u_fog_near  = 5.0;
uniform float u_fog_far   = 50.0;

out vec4 frag_color;

void main() {
    vec3 base = u_use_texture ? texture(u_texture, v_uv).rgb * u_color
                              : u_color;

    float fog_factor = clamp((u_fog_far + v_depth) / (u_fog_far - u_fog_near), 0.0, 1.0);
    vec3 final = mix(u_fog_color, base, fog_factor);

    frag_color = vec4(final, 1.0);
}
