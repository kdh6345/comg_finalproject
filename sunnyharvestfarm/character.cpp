#include "character.h"

// ������: ��ġ, ũ��, ���� �ʱ�ȭ
Character::Character(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color), rotationY(0.0f) {}

// �̵� �Լ�: ��ġ�� ����
void Character::move(float dx, float dy, float dz) {
    position.x += dx;
    position.y += dy;
    position.z += dz;
}

// ȸ�� �Լ�: Y�� ���� ȸ��
void Character::rotate(float angle) {
    rotationY += angle;
}

// ������ �Լ�: drawCube�� ȣ���Ͽ� ĳ���͸� ������
void Character::render(glm::vec3 lightPos, glm::vec3 viewPos) {
    // �� ��ȯ ��� ����
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);                // ��ġ �̵�
    model = glm::rotate(model, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // ȸ��
    drawCube(position, size, color, lightPos, viewPos);     // drawCube�� ������
}
