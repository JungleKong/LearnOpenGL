#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D noiseTexture;
uniform sampler2D circleTexture;

const float border = 0.5;
const float width = 800.0;
const float height = 800.0;

void main()
{
    float displacement = texture(noiseTexture, TexCoord).r;
    displacement = displacement - border;
    vec2 disCoord = TexCoord + vec2(displacement / 30.0);

    // if (disCoord.x < 0.0 || disCoord.x > 1.0 || disCoord.y < 0.0 || disCoord.y > 1.0) {
    //     discard;
    // }

    vec4 col = texture(circleTexture, disCoord).rgba;

    FragColor = vec4(col);
    // FragColor = vec4(texture(circleTexture, TexCoord).rgb, 1.0);
} 