#pragma once

#include "common.h"
#include "item.h"

class DropEgg;

class Customer {
private:
    glm::vec3 position;  // �մ��� ���� ��ġ
    glm::vec3 size;      // �մ��� ũ��
    glm::vec3 color;     // �մ��� ����
    float rotationY;     // �մ��� Y�� ȸ����
    glm::vec3 targetPosition;  // �̵� ��ǥ ��ġ
    glm::vec3 spawnPosition;   // �մ��� ���� ��ġ
    float speed;         // �̵� �ӵ�

    // ��ü ��Ʈ
    glm::vec3 bodyOffset, bodySize;
    glm::vec3 headOffset, headSize;
    glm::vec3 armSize, leftArmOffset, rightArmOffset;
    glm::vec3 legSize, leftLegOffset, rightLegOffset;

    // �ִϸ��̼� ����
    float leftArmSwing, rightArmSwing;
    float leftLegSwing, rightLegSwing;
    bool swingDirection;   // true: ������, false: �ڷ�
    bool isMoving;         // �̵� ������ ���� (�ִϸ��̼� ����)
    bool isResetting;      // �ȴٸ� ������ �ʱ�ȭ ������ ����

   

    // �߰� ����
    bool isRotating;        // ȸ�� ������ ����
    int rotationStage;      // ���� ȸ�� �ܰ� (0: ����, 1: ù ȸ��, 2: �� ��° ȸ��)
    glm::vec3 intermediateTarget; // ȸ�� �� �̵��� �߰� ��ǥ ��ġ

    std::vector<DropEgg> heldEggs; // �մ��� ��� �ִ� �ް�

public:
    void printState() const;
    Customer(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    bool isCarryingEggs;   // �ް��� ��� �ִ� ����
    void updatePosition(float deltaTime);  // ��ġ ������Ʈ
    void updateAnimation(float deltaTime); // �ȴٸ� �ִϸ��̼� ������Ʈ
    void render(glm::vec3 lightPos, glm::vec3 viewPos) const;  // �մ� ������
    bool isAtTarget() const;  // ��ǥ ������ �����ߴ��� Ȯ��
    void takeEggs(std::vector<DropEgg>& dropEggs); // �ް� ��������
    bool isAtSpawnPosition() const; // ���� ��ġ�� ���ƿԴ��� Ȯ��
    glm::vec3 getPosition() const;

    // �߰�: isCarryingEggs ���� ��ȯ
    bool isCarryingEggsStatus() const {
        return isCarryingEggs;
    }
};
