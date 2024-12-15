#include "globals.h"
#include "shaders.h"
#include "item.h"

// OpenGL 관련 전역 변수
GLuint shaderProgram;

GLuint axisVAO, axisVBO;
GLuint VAO, VBO;
glm::mat4 view, projection;

// 카메라 관련 전역 변수
glm::vec3 viewPos = glm::vec3(30.0f, 30.0f, 30.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraOrbitRadius = 12.0f;
float cameraOrbitAngle = 0.0f;
float cameraSpeed = 1.0f;
float orbitSpeed = glm::radians(5.0f);
//조명 관련 위치
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f); // 흰색 빛 (조명 색상)
glm::vec3 lightPos = glm::vec3(0.0f, 10.0f, 5.0f);
extern float lightOrbitRadius; // 공전 반경
extern float lightAngle;       // 공전 각도

// 로봇 상태 관련 전역 변수
glm::vec3 robotPosition = glm::vec3(0.0f, 0.0f, 0.0f);
float RobotX = 0.0f, RobotY = 0.0f, RobotZ = 0.0f;
bool walking = false;
float leftArmSwing = 0.0f, rightArmSwing = 0.0f;
float leftLegSwing = 0.0f, rightLegSwing = 0.0f;
bool swingDirection = true;

// 장애물 관련 전역 변수
glm::vec3 obstacles[3];
bool onObstacle = false;

// 기타 애니메이션 및 상태 변수
float moveStep = 0.05f;
bool key_w = false, key_a = false, key_s = false, key_d = false, key_j = false;

// 코인 초기화
int coins = 0;

//배경 관련 전역 변수
float ground_size = 20.0f;
bool dropping = false;