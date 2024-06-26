#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D inTexture;

const float width = 800.0;
const float height = 800.0;
const float PI = 3.141592653;

const int blurRadius = 15;  // blur半径
const vec2 blurOffset = vec2(1.0);  // blur步长
const float sumWeight = 0.996;

// 边界值处理
vec2 clampCoord(vec2 coord) {
    return vec2(clamp(coord.x, 0.0, 1.0), clamp(coord.y, 0.0, 1.0));
}

// 计算权重
float getWeight(int i) {
    float sigma = float(blurRadius) / 3.0;
    return (1.0 / sqrt(2.0 * PI * sigma * sigma)) * exp(-float(i * i) / (2.0 * sigma * sigma)) / sumWeight * 2.0;
}

// 高斯模糊效果
vec3 GaussianBlur(sampler2D inTexture, vec2 coord) {
    vec4 sourceColor = texture(inTexture, coord);
    float weight = getWeight(0);
    vec3 finalColor = sourceColor.rgb * weight;

    for (int i = 1; i < blurRadius; i++) {
        weight = getWeight(i);
        finalColor += texture(inTexture, clampCoord(coord - blurOffset * float(i))).rgb * weight;
        finalColor += texture(inTexture, clampCoord(coord + blurOffset * float(i))).rgb * weight;
    }
    return finalColor;
}

// 
vec3 CatmullRomBlur(vec2 coord) {
    return vec3(0.0);
}

void main()
{
    // vec3 color = GaussianBlur(inTexture, TexCoord);
    vec3 color = texture(inTexture, TexCoord).rgb;
    gl_FragColor = vec4(color, 1.0);
} 