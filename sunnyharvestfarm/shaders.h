#pragma once
#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>

// ���̴� �ε� �� ������
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);

#endif // SHADERS_H
