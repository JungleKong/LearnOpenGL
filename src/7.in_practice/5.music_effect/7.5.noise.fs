#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform float ;

const int State = 0;

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

float hash21(vec2 p)
{
    float h = dot(p, vec2(127.1, 311.7));
    return -1.0 + 2.0 * fract(sin(h) * 43758.5453123);
}

float ValueNoise(vec2 p)
{
    vec2 pi = floor(p);
    vec2 pf = fract(p);
    
    //vec2 w = pf * pf * (3.0 - 2.0 * pf);
    vec2 w = pf * pf * pf * (6 * pf * pf - 15 * pf + 10);
     
    return mix(mix(hash21(pi + vec2(0.0, 0.0)),hash21(pi + vec2(1.0, 0.0)), w.x),
                mix(hash21(pi + vec2(0.0, 1.0)), hash21(pi + vec2(1.0, 1.0)), w.x),w.y);
}

float ValueSum(vec2 p)
{
    float f = 0;
    p = p * 4;
    f += State > 0 ? abs(ValueNoise(p)) : ValueNoise(p);
    p = 2 * p;
    f += 0.5 * (State > 0 ? abs(ValueNoise(p)) : ValueNoise(p));
    p = 2 * p;
    f += 0.25 * (State > 0 ? abs(ValueNoise(p)) : ValueNoise(p));
    p = 2 * p;
    f += 0.125 * (State > 0 ? abs(ValueNoise(p)) : ValueNoise(p));
    p = 2 * p;
    f += 0.0625 * (State > 0 ? abs(ValueNoise(p)) : ValueNoise(p));
    
    p = 2 * p;
    if (State > 1)
        f = sin(f + p.x / 32.0);
    return f;
}

float SimplexNoise(vec2 p)
{
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;
    
    vec2 i = floor(p + (p.x + p.y) * K1);
    
    vec2 a = p - (i - (i.x + i.y) * K2);
    vec2 o = (a.x < a.y) ? vec2(0, 1) : vec2(1, 0);
    vec2 b = a - o + K2;
    vec2 c = a - 1 + 2 * K2;
    
    vec3 h = max(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0);
    vec3 n = pow(h, vec3(4.0)) * vec3(dot(a, hash22(i)), dot(b, hash22(i + o)),
        dot(c, hash22(i + 1)));
    
    return dot(vec3(70, 70, 70), n);
}

float SimplexSum(vec2 p)
{
    float f = 0;
    p = p * 4;
    f += State > 0 ? abs(SimplexNoise(p)) : SimplexNoise(p);
    p = 2 * p;
    f += 0.5 * (State > 0 ? abs(SimplexNoise(p)) : SimplexNoise(p));
    p = 2 * p;
    f += 0.25 * (State > 0 ? abs(SimplexNoise(p)) : SimplexNoise(p));
    p = 2 * p;
    f += 0.125 * (State > 0 ? abs(SimplexNoise(p)) : SimplexNoise(p));
    p = 2 * p;
    f += 0.0625 * (State > 0 ? abs(SimplexNoise(p)) : SimplexNoise(p));
    
    p = 2 * p;
    if (State > 1)
        f = sin(f + p.x / 32.0); 
    return f;
}

vec2 random2(vec2 p)
{
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)))) *
        43758.5453);
}

// float Worley(vec2 p)
// {
//     float min_dist = 1000;
//     vec2 pi = floor(p);
//     vec2 pf = fract(p);
//     float num = 800 / 10;
    
//     for (int m = -1; m <= 1; m++)
//     {
//         for (int n = -1; n <= 1; n++)
//         {
//             vec2 sp = (pi + vec2(m, n));
//             float factor = num;
//             float pos = int((sp + factor).x) % int(factor);
            
//             sp += random2(vec2(pos));
//             float dist = distance(p, sp);
//             min_dist = min(min_dist, dist);
//         }
//     }
//     return min_dist;
// }

const float PI = 3.141592653;
const float width = 800.0;
const float height = 800.0;

void main() {
	float grey = SimplexSum(TexCoord) * 0.5 + 0.5;  // [-1, 1] -> [0, 1]
    
	// float grey = SimplexSum(TexCoord);
    // grey = 1.0 / (1.0 + exp(grey * 5.0));

    // int range = 0;
    // float sum = 0.0;
    // for (int i = -range; i <= range; i++) {
    //     for (int j = -range; j <= range; j++) {
    //         vec2 st = TexCoord + vec2(float(i) / width, float(j) / height);
    //         float noise = SimplexSum(st);
    //         sum += 1.0 / (1.0 + exp(noise * 10.0));
    //     }
    // }
    // float grey = sum / ((2 * range + 1) * (2 * range + 1));

    gl_FragColor = vec4(vec3(grey), 1.0);
}