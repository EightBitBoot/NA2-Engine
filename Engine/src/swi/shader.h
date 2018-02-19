#pragma once

const char* vertexShader = R"(
#version 330 core

layout(location = 0) in vec2 pos;

uniform mat4 rotMat;

void main()
{
	gl_Position = rotMat * vec4(pos, 0.0f, 1.0f);
}
)";

const char* fragmentShader = R"(
#version 330 core

out vec4 outcolor;

void main()
{
	outcolor = vec4(1.0f, 0.0f, 1.0f, 1.0f);
}
)";