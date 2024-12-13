#include "character.h"

// 생성자: 위치, 크기, 색상 초기화
Character::Character(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color), rotationY(0.0f) {}

// 이동 함수: 위치를 변경
void Character::move(float dx, float dy, float dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

// 회전 함수: Y축 기준 회전
void Character::rotate(float angle) {
    rotationY += angle;
}

// 렌더링 함수: drawCube를 호출하여 캐릭터를 렌더링
void Character::render(glm::vec3 lightPos, glm::vec3 viewPos) {
    // 모델 변환 행렬 생성
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);                // 위치 이동
    model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // 회전
    drawCube(position, size, color, lightPos, viewPos);     // drawCube로 렌더링
}
