#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <vector>
#include "character.h"
#include "customer.h"

// OpenGL ���� ���� ����
extern GLuint shaderProgram;
extern GLuint axisVAO, axisVBO;
extern GLuint VAO, VBO;
extern glm::mat4 view, projection;

// ī�޶� ���� ���� ����
extern glm::vec3 lightPos;
extern glm::vec3 viewPos;
extern glm::vec3 cameraPos;
extern glm::vec3 cameraTarget;
extern glm::vec3 cameraUp;

extern float cameraOrbitRadius;
extern float cameraOrbitAngle;
extern float cameraSpeed;
extern float orbitSpeed;

// �κ� ���� ���� ���� ����
extern glm::vec3 robotPosition;

extern float RobotX, RobotY, RobotZ;
extern bool walking;
extern float leftArmSwing, rightArmSwing;
extern float leftLegSwing, rightLegSwing;
extern bool swingDirection;

// ��ֹ� ���� ���� ����
extern glm::vec3 obstacles[3];
extern bool onObstacle;


// ��Ÿ �ִϸ��̼� �� ���� ����
extern float moveStep;
extern bool key_w, key_a, key_s, key_d, key_j;

//��� ���� ���� ����
extern float ground_size;
extern bool dropping;
#endif // GLOBALS_H

