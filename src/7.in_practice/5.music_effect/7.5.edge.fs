#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D edgeInTexture;

const float width = 800.0;
const float height = 800.0;

const float sampleStep = 11.0;
const float delta = sampleStep / width;
const float factor = 4.741;

void main()
{
    vec4 centerColor = texture(edgeInTexture, TexCoord);

    float edgeFactor = 0.0;
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2(-delta, -delta)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2(-delta,  delta)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2( delta, -delta)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2( delta,  delta)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2(-delta, 0.0)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2( delta, 0.0)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2( 0.0, -delta)) - centerColor);
    edgeFactor += length(texture(edgeInTexture, TexCoord + vec2( 0.0,  delta)) - centerColor);

    gl_FragColor = vec4(edgeFactor / factor);
    
}