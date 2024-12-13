#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H

#include "common.h"
#include "globals.h"
#include "draw_cube.h"

class Character {
private:
    glm::vec3 position;  // ĳ������ ��ġ
    glm::vec3 size;      // ĳ������ ũ��
    glm::vec3 color;     // ĳ������ ����
    float rotationY;     // ĳ������ Y�� ȸ�� ����

public:
    // ������
    Character(glm::vec3 position, glm::vec3 size, glm::vec3 color);

    // ĳ���� �̵�
    void move(float dx, float dy, float dz);

    // ĳ���� ȸ��
    void rotate(float angle);

    // ĳ���� ������
    void render(glm::vec3 lightPos, glm::vec3 viewPos);
};

#endif // CHARACTER_H

