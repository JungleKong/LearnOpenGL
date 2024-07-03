#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D scaleInTexture;

const float border = 0.8;
const float width = 800.0;
const float height = 800.0;
const float centerX = 0.5;  // 缩放的中心点
const float centerY = 0.5;  // 缩放的中心点
const float alphaBack = 0.995;
const float scaleBack = 1.003;

void main()
{
    vec2 normCoord = (2.0 * TexCoord - 1.0);
    vec2 uvBack = (vec2(normCoord.x, normCoord.y * height / width) / scaleBack + 1.0) / 2.0;
    
    gl_FragColor = texture(scaleInTexture, uvBack);
    // gl_FragColor = vec4(transparentColor.rgb, transparentColor.a * alphaBack);
} 