#version 460 core

in vec2 uvs;
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

float t = iTime;
vec2 r = iResolution;
vec2 fragCoord = uvs * iResolution;




void main()
{
    vec2 uv = uvs *2.0 -1.0;
    float aspect = iResolution.x/iResolution.y;
    uv.x *= aspect;
    FragColor = vec4(uv, 0.0, 1.0);
}
