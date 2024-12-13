#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include "globals.h"
#include "draw_cube.h"

class Character {
private:
    glm::vec3 position;  // 캐릭터의 위치
    glm::vec3 size;      // 캐릭터의 크기
    glm::vec3 color;     // 캐릭터의 색상
    float rotationY;     // 캐릭터의 Y축 회전 각도

    // 상대적 위치와 크기 (각 부위의 속성)
    glm::vec3 bodyOffset; // 몸통 위
    glm::vec3 bodySize;
    glm::vec3 headOffset;
    glm::vec3 headSize;
    glm::vec3 armSize;
    glm::vec3 leftArmOffset;
    glm::vec3 rightArmOffset;
    glm::vec3 legSize;
    glm::vec3 leftLegOffset;
    glm::vec3 rightLegOffset;

public:
    // 생성자
    Character(glm::vec3 position, glm::vec3 size, glm::vec3 color);

    // 캐릭터 이동
    void move(float dx, float dy, float dz);

    // 캐릭터 회전
    void rotate(float angle);

    // 캐릭터 렌더링
    void render(glm::vec3 lightPos, glm::vec3 viewPos);
};

#endif // CHARACTER_H

