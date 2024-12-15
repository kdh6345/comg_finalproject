#pragma once
#ifndef DRAW_CUBE_H
#define DRAW_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common.h"
#include "globals.h"

// 큐브 초기화 함수
void initCube();

// 큐브 그리기 함수
void drawCube(glm::vec3 position, glm::vec3 size, glm::vec3 color, glm::vec3 lightPos, glm::vec3 viewPos, glm::mat4 model);
void drawCylinder(float baseRadius, float topRadius, float height, int slices, int stacks);
void drawCylinderWithCaps(float baseRadius, float topRadius, float height, int slices, int stacks);
#endif // DRAW_CUBE_H

