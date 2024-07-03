#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D displaceTexture;
uniform sampler2D sourceTexture;

const float width = 800.0;
const float height = 800.0;

const vec2 midpoint = vec2(0.5, 0.5);
const vec2 displaceWeight = vec2(0.026, 0.026);

// 边界值处理 const char* extend = "hold"
vec2 edgeCoord(vec2 coord) {
    return vec2(clamp(coord.x, 0.0, 1.0), clamp(coord.y, 0.0, 1.0));
}

void main()
{
    vec2 displacement = texture(displaceTexture, TexCoord).rg;
    displacement -= midpoint;
    displacement *= displaceWeight * 5.0;
    vec2 disCoord = TexCoord + displacement;

    disCoord = edgeCoord(disCoord);

    FragColor = texture(sourceTexture, disCoord);
} 