#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D transparentTexture;

const float border = 0.8;
const float width = 800.0;
const float height = 800.0;
const float centerX = 0.5;  // 缩放的中心点
const float centerY = 0.5;  // 缩放的中心点
const float alphaBack = 0.982;
const float scaleBack = 1.003;

void main()
{
    vec4 transparentColor = texture(transparentTexture, TexCoord);
    gl_FragColor = transparentColor * alphaBack;
} 