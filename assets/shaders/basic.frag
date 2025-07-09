#version 460 core

in vec2 uvs;
out vec4 FragColor;

uniform vec2 iResolution;
uniform float iTime;

float t = iTime;
vec2 r = iResolution;




void main()
{
    vec2 fragCoord = uvs * iResolution;

    vec2 uv = uvs *2.0 -1.0;
    float aspect = iResolution.x/iResolution.y;
    uv.x *= aspect;
    
    float distance =length(uv);
    FragColor.rgb = vec3(distance);
      
    
}
