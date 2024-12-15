#include "globals.h"
#include "shaders.h"
#include "item.h"

// OpenGL ���� ���� ����
GLuint shaderProgram;

GLuint axisVAO, axisVBO;
GLuint VAO, VBO;
glm::mat4 view, projection;

// ī�޶� ���� ���� ����
glm::vec3 viewPos = glm::vec3(30.0f, 30.0f, 30.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraOrbitRadius = 12.0f;
float cameraOrbitAngle = 0.0f;
float cameraSpeed = 1.0f;
float orbitSpeed = glm::radians(5.0f);
//���� ���� ��ġ
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // ��� �� (���� ����)
glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 5.0f);
extern float lightOrbitRadius; // ���� �ݰ�
extern float lightAngle;       // ���� ����

// �κ� ���� ���� ���� ����
glm::vec3 robotPosition = glm::vec3(0.0f, 0.0f, 0.0f);
float RobotX = 0.0f, RobotY = 0.0f, RobotZ = 0.0f;
bool walking = false;
float leftArmSwing = 0.0f, rightArmSwing = 0.0f;
float leftLegSwing = 0.0f, rightLegSwing = 0.0f;
bool swingDirection = true;

// ��ֹ� ���� ���� ����
glm::vec3 obstacles[3];
bool onObstacle = false;

// ��Ÿ �ִϸ��̼� �� ���� ����
float moveStep = 0.05f;
bool key_w = false, key_a = false, key_s = false, key_d = false, key_j = false;

// ���� �ʱ�ȭ
int coins = 0;

//��� ���� ���� ����
float ground_size = 20.0f;
bool dropping = false;