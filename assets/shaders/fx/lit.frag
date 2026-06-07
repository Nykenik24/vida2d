#version 330 core
in vec2 v_uv;
in vec3 v_normal;
in vec3 v_frag_pos;

uniform vec3 u_color;
uniform sampler2D u_texture;
uniform int u_use_texture;
uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform float u_ambient;

out vec4 frag_color;

void main() {
    vec3 base = u_use_texture == 1 ? texture(u_texture, v_uv).rgb * u_color : u_color;
    vec3 normal = normalize(v_normal);
    float diffuse = max(dot(normal, u_light_dir), 0.0);
    vec3 lighting = (u_ambient + diffuse) * u_light_color;
    frag_color = vec4(base * lighting, 1.0);
}
