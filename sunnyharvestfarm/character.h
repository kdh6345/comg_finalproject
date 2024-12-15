#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include "common.h"
#include "globals.h"
#include "draw_cube.h"
#include "collision_object.h"

class Character {
private:
    glm::vec3 position;  // ĳ������ ��ġ
    glm::vec3 size;      // ĳ������ ũ��
    glm::vec3 color;     // ĳ������ ����
    float rotationY;     // ĳ������ Y�� ȸ�� ����
    float targetRotationY; // ��ǥ Y�� ȸ�� ����

    // ����� ��ġ�� ũ�� (�� ������ �Ӽ�)
    glm::vec3 bodyOffset; // ���� ��
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
    // ������
    Character(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    // ĳ���� �̵�
    void move(float dx, float dy, float dz, const CollisionManager& collisionManager);

    // ���� Y�� ȸ�� ���� ��ȯ
    float getRotationY() const {
        return rotationY;
    }

    // ��ǥ Y�� ȸ�� ���� ����
    void setTargetRotation(float angle);

    glm::vec3 getPosition()const;
    glm::vec3 getSize() const;

    // ȸ�� ������Ʈ
    void updateRotation();

    // ĳ���� ������
    void render(glm::vec3 lightPos, glm::vec3 viewPos);
};



#endif // CHARACTER_H

