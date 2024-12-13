#pragma once
#ifndef DRAW_CUBE_H
#define DRAW_CUBE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "common.h"
#include "globals.h"

// ť�� �ʱ�ȭ �Լ�
void initCube();

// ť�� �׸��� �Լ�
void drawCube(glm::vec3 position, glm::vec3 size, glm::vec3 color, glm::vec3 lightPos, glm::vec3 viewPos);

#endif // DRAW_CUBE_H

