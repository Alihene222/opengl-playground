#version 150

in vec3 aPos;
in vec2 aTexCoords;
in float aTexId;

out vec2 vTexCoords;
out float vTexId;

out vec3 vColor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_time;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(aPos, 1.0);
    vTexCoords = aTexCoords;
    vTexId = aTexId;
    vColor = aPos * abs(sin(u_time));
}