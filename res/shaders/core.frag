#version 150

in vec2 vTexCoords;
in float vTexId;
in vec3 vColor;

out vec4 color;

uniform sampler2D u_textures[16];

void main() {
    int texId = int(vTexId);
    switch(texId) {
        case 0:
            color = texture(u_textures[0], vTexCoords) * vec4(vColor + 0.5, 1.0);
            break;
    }
}