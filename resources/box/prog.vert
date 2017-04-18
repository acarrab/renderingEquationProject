#version 330 core

out vec3 fragmentColor;

layout(location = 0) in vec3 vertexPosition;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(vertexPosition, 1.0);
    fragmentColor = vec3(1.0,0.0,0.0);
}
