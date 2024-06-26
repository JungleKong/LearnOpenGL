#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;



uniform sampler2D feedbackTexture;

const float width = 800.0;
const float height = 800.0;

const float gamma = 1.74;
const float contrast = 1.69;

vec3 rgb2hsv(vec3 c) {
    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

    float d = q.x - min(q.w, q.y);
    float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}

void main()
{
    vec4 color = texture(feedbackTexture, TexCoord);
    float grey = 0.5 * (color.r * 0.299 + color.g * 0.587 + color.g * 0.114) + color.a * 0.5;
    // float grey = rgb2hsv(color.rgb).z;

    float gammaGrey = pow(grey, 0.74);
    float contrastGrey = 1.0 / (1.0 + exp(-(gammaGrey - 0.5) * 2.0 * contrast));

    gl_FragColor = vec4(vec3(contrastGrey), 1.0);
    // gl_FragColor = vec4(texture(feedbackTexture, TexCoord).rgb, 1.0);
}