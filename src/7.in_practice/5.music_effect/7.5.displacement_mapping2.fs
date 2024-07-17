#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D noiseTexture;
uniform sampler2D circleTexture;

uniform float time;

const vec2 midpoint = vec2(0.5, 0.5);
const vec2 displaceWeight = vec2(1.0, 1.0);
const float width = 800.0;
const float height = 800.0;

const float ratio = 1.0 / 0.4;  // 色轮重复2.5次

const float pos[6] = float[6](0.0, 0.14861462, 0.3425693, 0.51385397, 0.6423174, 0.8565233);
const vec3 color[6] = vec3[6](
    vec3(0.0,           0.0,        0.0         ),
    vec3(0.115,         0.0,        0.07475001  ),
    vec3(0.69973546,    0.46850398, 0.964       ),
    vec3(0.21303202,    0.76210475, 0.859       ),
    vec3(0.1403334,     0.0,        0.421       ),
    vec3(0.015030005,   0.12435943, 0.835       )
);

vec2 clampCoord(vec2 coord) {
    return vec2(clamp(coord.x, 0.0, 1.0), clamp(coord.y, 0.0, 1.0));
}

vec3 hsv2rgb(vec3 c) {
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

float getRadius(vec2 coord) {
    vec2 normCoord = 2.0 * coord - 1.0; // Norm to [-1,1]
    return length(vec2(normCoord.x, normCoord.y * height / width)) * ratio - time; // Scale to achieve 2.5 cycles
}

vec3 getColor(float radius) {
    vec3 resultColor = color[5]; // Default to last color
    float adjustedPos = fract(radius); // Adjust for cycle repetition
    
    for(int i = 0; i < 6; ++i) {
        if(i == 5 || (pos[i] <= adjustedPos && adjustedPos < pos[i + 1])) {
            float t = 0.0;
            if(i != 5) {
                t = (adjustedPos - pos[i]) / (pos[i + 1] - pos[i]);
                resultColor = mix(color[i], color[(i + 1) % 6], t);
            } else if (i == 5) {
                t = (adjustedPos - pos[5]) / (1.0 - pos[5]);
                resultColor = mix(color[5], color[(0) % 6], t);
            }
            break;
        }
    }
    return resultColor;
}

void main()
{
    vec2 displacement = texture(noiseTexture, TexCoord).rr;
    // displacement -= midpoint;
    // vec2 disCoord = TexCoord + displacement * displaceWeight * 2.0;
    vec2 disCoord = TexCoord + vec2(displacement.x - 0.5, displacement.y - 0.5) * 2.0;
    disCoord = clampCoord(disCoord);
    vec3 col = texture(circleTexture, disCoord).rgb;

    // difference
    vec3 differenceColor = abs(texture(circleTexture, TexCoord).rgb - col);

    // grey
    float grey = differenceColor.r * 0.299 + differenceColor.g * 0.587 + differenceColor.g * 0.114;

    // mask
    // float blackLevel = clamp(grey, 0.16, 1.0);
    float blackLevel = grey * step(0.32, grey);
    float gammaGrey = pow(blackLevel, 1.0 / 0.83);


    float radius = getRadius(vec2(grey, 0.0));
    vec3 rampCol = getColor(radius);

    vec3 outColor;

    // overlay
    if (gammaGrey < 0.5) {
        outColor = 2.0 * gammaGrey * rampCol;
    } else {
        outColor = 1.0 - 2.0 * (1.0 - gammaGrey) * (1.0 - rampCol);
    }

    gl_FragColor = vec4(getColor(getRadius(TexCoord)), 1.0);

    // noise color
    // gl_FragColor = vec4(texture(noiseTexture, TexCoord).rgb, 1.0);

    // 
    // gl_FragColor = vec4(texture(circleTexture, TexCoord).rgb, 1.0);

    // displacement mapping color
    // gl_FragColor = vec4(col, 1.0);

    // // difference color
    // gl_FragColor = vec4(differenceColor, 1.0);

    // overlay
    // gl_FragColor = vec4(vec3(grey), 1.0);


    // rampCol
    // gl_FragColor = vec4(vec3(rampCol), 1.0);

    // final out color
    gl_FragColor = vec4(outColor, 1.0);

} 