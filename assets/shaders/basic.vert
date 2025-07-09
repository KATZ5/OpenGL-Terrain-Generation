#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texpos;
out vec2 uvs;
void main()
{
gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
uvs = texpos;
}

