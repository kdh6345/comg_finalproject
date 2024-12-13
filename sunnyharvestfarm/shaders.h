#pragma once
#ifndef SHADERS_H
#define SHADERS_H

#include <GL/glew.h>
#include <string>

// 쉐이더 로드 및 컴파일
GLuint createShaderProgram(const char* vertexPath, const char* fragmentPath);

#endif // SHADERS_H
