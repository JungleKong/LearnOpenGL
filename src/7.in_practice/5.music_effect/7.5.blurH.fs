#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D inTexture;

const int shrink = 8;
const float width = 800.0 / 8;
const float height = 800.0 / 8;
const float PI = 3.141592653;

const int blurRadius = 15;  // blur半径
const float blurOffset = 1.0;  // blur步长
const float sumWeight = 0.996;

// 边界值处理 const char* extend = "hold"
vec2 edgeCoord(vec2 coord) {
    return vec2(clamp(coord.x, 0.0, 1.0), clamp(coord.y, 0.0, 1.0));
}

// 计算权重
float getWeight(int i) {
    float sigma = float(blurRadius) / 3.0;
    return (1.0 / sqrt(2.0 * PI * sigma * sigma)) * exp(-float(i * i) / (2.0 * sigma * sigma)) / sumWeight;
    // return 1.0 / (blurRadius * 2.0 - 1);
}

// 高斯模糊效果
vec4 GaussianBlur(sampler2D inTexture, vec2 coord) {
    vec4 sourceColor = texture(inTexture, coord);
    float weight = getWeight(0);
    vec4 finalColor = sourceColor * weight;

    for (int i = 1; i < blurRadius; i++) {
        weight = getWeight(i);
        finalColor += texture(inTexture, edgeCoord(vec2(coord.x, coord.y - blurOffset * float(i) / height))) * weight;
        finalColor += texture(inTexture, edgeCoord(vec2(coord.x, coord.y + blurOffset * float(i) / height))) * weight;
    }
    return finalColor;
}

// 
vec3 CatmullRomBlur(vec2 coord) {
    return vec3(0.0);
}

void main()
{
    gl_FragColor = GaussianBlur(inTexture, TexCoord);
    // gl_FragColor = texture(inTexture, TexCoord);
} 