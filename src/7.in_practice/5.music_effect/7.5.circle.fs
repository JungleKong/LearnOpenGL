#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float centerX;
uniform float centerY;
uniform float radius;  // 圆环的内半径
uniform float hue;
uniform float time;

const int State = 0;
const float blur = 0.18;  // 圆环边缘的模糊半径
const float ringWidth = 0.0001;  // 圆环的宽度
const float width = 800.0;
const float height = 800.0;
const float sat = 1.0;
const float value = 1.0;

const float PI = 3.141592653;
const int blurRadius = 15;  // blur半径
const vec2 blurOffset = vec2(1.0);  // blur步长
const float sumWeight = 0.996;


vec2 hash22(vec2 p)
{
    p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));
    return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);  // [-1, 1]
}

float Perlin(vec2 p)
{
    vec2 pi = floor(p);//返回小于等于x的最大整数。
    vec2 pf = fract(p);//返回输入值的小数部分。
    
    //vec2 w = pf * pf * (3.0 - 2.0 * pf);
    vec2 w = pf * pf * pf * (6 * pf * pf - 15 * pf + 10);
     
    return mix(mix(dot(hash22(pi + vec2(0.0, 0.0)), pf - vec2(0.0, 0.0)),
                    dot(hash22(pi + vec2(1.0, 0.0)), pf - vec2(1, 0.0)), w.x),
                mix(dot(hash22(pi + vec2(0.0, 1.0)), pf - vec2(0.0, 1.0)),
                    dot(hash22(pi + vec2(1.0, 1.0)), pf - vec2(1.0, 1.0)), w.x), w.y);
}

float PerlinSum(vec2 p)
{
    float f = 0;
    p = p * 8;
    mat2 m = mat2(1.6, 1.2, -1.2, 1.6);
    
    f += 1.0 * (State > 0 ? abs(Perlin(p)) : Perlin(p));
    p = m * p;
    f += 0.5 * (State > 0 ? abs(Perlin(p)) : Perlin(p));
    p = m * p;
    f += 0.25 * (State > 0 ? abs(Perlin(p)) : Perlin(p));
    p = m * p;
    f += 0.125 * (State > 0 ? abs(Perlin(p)) : Perlin(p));
    p = m * p;
    f += 0.0625 * (State > 0 ? abs(Perlin(p)) : Perlin(p));
    
    p = m * p;
    if (State > 1)
        f = sin(f + p.x / 32.0);
    return f;
}


vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void main() {
    float innerRadius = radius; // 圆环的内半径
    float outerRadius = radius + ringWidth; // 圆环的外半径

    float center_x = 0.5 + PerlinSum(vec2(sin(time / 30.0) * 0.5 + 0.5, int(time * 10.0) % int(width) / 800.0)) * 0.5;
    float center_y = 0.5 + PerlinSum(vec2(cos(time / 30.0) * 0.5 + 0.5, int(time * 10.0) % int(width) / 800.0)) * 0.5;

    // 计算片段到圆心的距离
    float dist = length(vec2(TexCoord.x, (TexCoord.y - 0.5) * height / width + 0.5) - vec2(center_x, center_y)); // 假设圆心在纹理的中心

    // // 利用smoothstep产生圆环的模糊边缘
    // float alpha = smoothstep(innerRadius - blur, innerRadius, dist) *
    //              (1.0 - smoothstep(outerRadius, outerRadius + blur, dist));

    // float weight = 4.0 / 11.1;
    // vec3 color = hsv2rgb(vec3(hue, sat, value));
    // gl_FragColor = vec4(min(weight * alpha, color.r), min(weight * alpha, color.g), min(weight * alpha, color.b), weight * alpha); // 使用alpha通道控制透明度

    gl_FragColor = vec4(step(dist, radius));

}