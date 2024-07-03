#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D inTexture;

const float width = 800.0;
const float height = 800.0;
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
    return (1.0 / sqrt(2.0 * PI * sigma * sigma)) * exp(-float(i * i) / (2.0 * sigma * sigma)) / sumWeight * 2.0;
}

// 高斯模糊效果
vec4 GaussianBlur(sampler2D inTexture, vec2 coord) {
    vec4 finalColor = vec4(0.0);
    finalColor += texture(inTexture, coord);

    for (int i = 1; i <= blurRadius; i++) {
        finalColor += texture(inTexture, edgeCoord(coord + vec2(float( i) / width, 0)));
        finalColor += texture(inTexture, edgeCoord(coord + vec2(float(-i) / width, 0)));
    }

    for (int j = 1; j <= blurRadius; j++) {
        finalColor += texture(inTexture, edgeCoord(coord + vec2(0, float( j) / height)));
        finalColor += texture(inTexture, edgeCoord(coord + vec2(0, float(-j) / height)));
    }

    for (int i = 1; i <= blurRadius; i++) {
        for (int j = 1; j <= blurRadius; j++) {
            finalColor += texture(inTexture, edgeCoord(coord + vec2(float(i ) / width, float( j) / height)));
            finalColor += texture(inTexture, edgeCoord(coord + vec2(float(-i) / width, float( j) / height)));
            finalColor += texture(inTexture, edgeCoord(coord + vec2(float(i ) / width, float(-j) / height)));
            finalColor += texture(inTexture, edgeCoord(coord + vec2(float(-i) / width, float(-j) / height)));
        }
    }

    return finalColor / ((blurRadius * 2.0 + 1) * (blurRadius * 2.0 + 1));
}

// 
vec4 CatmullRomBlur(vec2 coord) {
    return vec4(0.0);
}

void main()
{
    vec4 color = GaussianBlur(inTexture, TexCoord);
    // vec3 color = texture(inTexture, TexCoord).rgb;
    gl_FragColor = vec4(color);
} 