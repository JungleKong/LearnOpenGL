#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D feedbackTexture;
uniform sampler2D circleMappingTexture;

const float border = 0.8;
const float width = 800.0;
const float height = 800.0;
const float centerX = 0.5;  // 缩放的中心点
const float centerY = 0.5;  // 缩放的中心点
const float alphaBack = 0.9;
const float scaleBack = 1.003;

void main()
{
    vec2 normCoord = (2.0 * TexCoord - 1.0);
    vec2 uvBack = (vec2(normCoord.x, normCoord.y * height / width) / scaleBack + 1.0) / 2.0;

    // vec2 uvBack = (TexCoord - 0.5) / scaleBack + 0.5;
    
    vec4 input1 = texture(feedbackTexture, uvBack);
    vec4 input2 = texture(circleMappingTexture, TexCoord);

    vec4 overColor = input2 * (1.0 - input1.a) + input1;

    gl_FragColor = overColor;
} 