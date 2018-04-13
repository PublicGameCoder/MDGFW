
#version 330 core
varying vec2 UV;
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec3 textColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(myTextureSampler, UV).r);
    color = vec4(textColor, 1.0) * sampled;
}  