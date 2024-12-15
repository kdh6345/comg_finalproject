#ifndef ITEM_H
#define ITEM_H

#include "common.h"
#include "draw_cube.h"

class Egg {
public:
    Egg(glm::vec3 position, glm::vec3 size, glm::vec3 color);

    glm::vec3 getPosition() const;
    glm::vec3 getSize() const;
    glm::vec3 getColor() const; // ���� ��ȯ
    void render(glm::vec3 lightPos, glm::vec3 viewPos) const;


protected: // �ڽ� Ŭ�������� ���� ����
    glm::vec3 position; // ��ġ
    glm::vec3 size;     // ũ��
    glm::vec3 color;    // ����
};

class HoldingEgg {
public:
    HoldingEgg(glm::vec3 startPosition, glm::vec3 targetOffset, glm::vec3 size, glm::vec3 color);

    void updatePosition(glm::vec3 basePosition, float deltaTime);
    void render(glm::vec3 lightPos, glm::vec3 viewPos) const;
    glm::vec3 getPosition() const;
    glm::vec3 getCurrentPosition() const;
    glm::vec3 getSize() const;
    glm::vec3 getColor() const; // ���� ��ȯ

private:
    glm::vec3 currentPosition;
    glm::vec3 targetOffset;
    glm::vec3 size;
    glm::vec3 color;
};

class DropEgg {
public:
    DropEgg(glm::vec3 startPosition, glm::vec3 targetPosition, glm::vec3 size, glm::vec3 color);

    void updatePosition(float deltaTime);
    void render(glm::vec3 lightPos, glm::vec3 viewPos) const;
    bool isAtTarget() const;
    void renderAtPosition(glm::vec3 position, glm::vec3 lightPos, glm::vec3 viewPos) const;

private:
    glm::vec3 currentPosition; // ���� ��ġ
    glm::vec3 targetPosition;  // ��ǥ ��ġ
    glm::vec3 size;            // ũ��
    glm::vec3 color;           // ����
};

// DropEgg ����Ʈ ����
void addDropEgg(glm::vec3 startPosition, glm::vec3 targetPosition, glm::vec3 size, glm::vec3 color);
void updateDropEggs(float deltaTime);
void renderDropEggs(glm::vec3 lightPos, glm::vec3 viewPos);

#endif // ITEM_H
