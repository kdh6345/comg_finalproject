#version 330 core

layout(location = 0) in vec3 aPos;  // 정점 위치
layout(location = 1) in vec3 aNormal;  // 정점 법선

out vec3 FragPos;  // 프래그먼트 셰이더로 전달
out vec3 Normal;   // 프래그먼트 셰이더로 전달

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
