#include "character.h"

// 생성자: 몸통과 각 부위의 상대적 위치 및 크기 초기화
Character::Character(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color), rotationY(0.0f) {

    bodyOffset = glm::vec3(position.x, position.y , position.z); // 몸통 위
    bodySize = glm::vec3(1.0f, 1.0f, 0.5f);
    // 머리
    headOffset = glm::vec3(0.0f, position.y + 1.25f, 0.0f); // 몸통 위
    headSize = glm::vec3(1.5f, 1.5f, 1.5f);

    // 팔
    armSize = glm::vec3(0.25f, 1.0f, 0.3f);
    leftArmOffset = glm::vec3(position.x - 0.75f, position.y , 0.0f); // 몸통 왼쪽
    rightArmOffset = glm::vec3(position.x + 0.75f, position.y , 0.0f); // 몸통 오른쪽

    // 다리
    legSize = glm::vec3(0.3f, 0.5f, 0.3f);
    leftLegOffset = glm::vec3(position.x - 0.35f, position.y -0.75, 0.0f); // 몸통 왼쪽 아래
    rightLegOffset = glm::vec3(position.x +0.35f, position.y-0.75, 0.0f); // 몸통 오른쪽 아래
}

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

// 렌더링 함수
void Character::render(glm::vec3 lightPos, glm::vec3 viewPos) {
    // 모델 변환 행렬 생성 (몸통 기준)
    glm::mat4 baseModel = glm::mat4(1.0f);
    baseModel = glm::translate(baseModel, position);                // 몸통 위치
    baseModel = glm::rotate(baseModel, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // 몸통 회전

    // 몸통 렌더링
    glm::mat4 bodyModel = glm::translate(baseModel, headOffset);
    drawCube(position + bodyOffset, bodySize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos);

    // 머리 렌더링
    glm::mat4 headModel = glm::translate(baseModel, headOffset);
    drawCube(position + headOffset, headSize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos);

    // 왼팔 렌더링
    glm::mat4 leftArmModel = glm::translate(baseModel, leftArmOffset);
    drawCube(position + leftArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos);

    // 오른팔 렌더링
    glm::mat4 rightArmModel = glm::translate(baseModel, rightArmOffset);
    drawCube(position + rightArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos);

    // 왼다리 렌더링
    glm::mat4 leftLegModel = glm::translate(baseModel, leftLegOffset);
    drawCube(position + leftLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos);

    // 오른다리 렌더링
    glm::mat4 rightLegModel = glm::translate(baseModel, rightLegOffset);
    drawCube(position + rightLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos);
}