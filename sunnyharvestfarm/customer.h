#pragma once

#include "common.h"
#include "item.h"

class DropEgg;

class Customer {
private:
    glm::vec3 position;  // 손님의 현재 위치
    glm::vec3 size;      // 손님의 크기
    glm::vec3 color;     // 손님의 색상
    float rotationY;     // 손님의 Y축 회전각
    glm::vec3 targetPosition;  // 이동 목표 위치
    glm::vec3 spawnPosition;   // 손님의 스폰 위치
    float speed;         // 이동 속도

    // 신체 파트
    glm::vec3 bodyOffset, bodySize;
    glm::vec3 headOffset, headSize;
    glm::vec3 armSize, leftArmOffset, rightArmOffset;
    glm::vec3 legSize, leftLegOffset, rightLegOffset;

    // 애니메이션 상태
    float leftArmSwing, rightArmSwing;
    float leftLegSwing, rightLegSwing;
    bool swingDirection;   // true: 앞으로, false: 뒤로
    bool isMoving;         // 이동 중인지 여부 (애니메이션 제어)
    bool isResetting;      // 팔다리 각도를 초기화 중인지 여부

   

    // 추가 상태
    bool isRotating;        // 회전 중인지 여부
    int rotationStage;      // 현재 회전 단계 (0: 없음, 1: 첫 회전, 2: 두 번째 회전)
    glm::vec3 intermediateTarget; // 회전 후 이동할 중간 목표 위치

    std::vector<DropEgg> heldEggs; // 손님이 들고 있는 달걀

public:
    void printState() const;
    Customer(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    bool isCarryingEggs;   // 달걀을 들고 있는 상태
    void updatePosition(float deltaTime);  // 위치 업데이트
    void updateAnimation(float deltaTime); // 팔다리 애니메이션 업데이트
    void render(glm::vec3 lightPos, glm::vec3 viewPos) const;  // 손님 렌더링
    bool isAtTarget() const;  // 목표 지점에 도달했는지 확인
    void takeEggs(std::vector<DropEgg>& dropEggs); // 달걀 가져가기
    bool isAtSpawnPosition() const; // 스폰 위치로 돌아왔는지 확인
    glm::vec3 getPosition() const;

    // 추가: isCarryingEggs 상태 반환
    bool isCarryingEggsStatus() const {
        return isCarryingEggs;
    }
};
