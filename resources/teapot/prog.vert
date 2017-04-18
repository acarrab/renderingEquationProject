#version 330 core

out vec4 fragmentColor;

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 textureCoord;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 vertexTangentX;
layout(location = 4) in vec3 vertexTangentY;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPosition, 1.0);
    fragmentColor = vec4(1.0, 0.0, 0.0, 1.0);
}
