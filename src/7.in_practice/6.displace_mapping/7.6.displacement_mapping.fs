#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D displaceTexture;
uniform sampler2D sourceTexture;

const float width = 800.0;
const float height = 800.0;

const vec2 midpoint = vec2(0.5, 0.5);
const vec2 displaceWeight = vec2(1.0, 1.0);

// 边界值处理 const char* extend = "hold"
vec2 edgeCoord(vec2 coord) {
    return vec2(clamp(coord.x, 0.00001, 0.99999), clamp(coord.y, 0.00001, 0.9999));
}

vec3 compositeOverlay(vec3 lookup, float level) {
    vec3 outColor;
    if (level < 0.5) {
        outColor = 2.0 * level * lookup;
    } else {
        outColor = 1.0 - 2.0 * (1.0 - level) * (1.0 - lookup);
    }
    return outColor;
}

void main()
{
    vec2 displacement = texture(displaceTexture, TexCoord).rg;
    displacement -= midpoint;
    displacement *= displaceWeight * 2.0;
    vec2 disCoord = TexCoord + displacement;
    // vec2 disCoord = TexCoord + vec2(displacement.x - 0.5, displacement.y - 0.5) * 2.0;  // * (720.0 / 1280.0, 1.0);

    disCoord = edgeCoord(disCoord);

    FragColor = texture(sourceTexture, disCoord);
    // FragColor = vec4(vec3(disCoord.y), 1.0);

    // vec4 lookup = texture(displaceTexture, vec2(TexCoord.x, 1.0 - TexCoord.y));
    // vec4 level = texture(sourceTexture, vec2(TexCoord.x, 1.0 - TexCoord.y));

    // FragColor = vec4(compositeOverlay(lookup.rgb, level.g), 1.0);
} 