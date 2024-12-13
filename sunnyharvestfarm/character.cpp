#include "character.h"

// ������: ����� �� ������ ����� ��ġ �� ũ�� �ʱ�ȭ
Character::Character(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color), rotationY(0.0f) {

    bodyOffset = glm::vec3(position.x, position.y , position.z); // ���� ��
    bodySize = glm::vec3(1.0f, 1.0f, 0.5f);
    // �Ӹ�
    headOffset = glm::vec3(0.0f, position.y + 1.25f, 0.0f); // ���� ��
    headSize = glm::vec3(1.5f, 1.5f, 1.5f);

    // ��
    armSize = glm::vec3(0.25f, 1.0f, 0.3f);
    leftArmOffset = glm::vec3(position.x - 0.75f, position.y , 0.0f); // ���� ����
    rightArmOffset = glm::vec3(position.x + 0.75f, position.y , 0.0f); // ���� ������

    // �ٸ�
    legSize = glm::vec3(0.3f, 0.5f, 0.3f);
    leftLegOffset = glm::vec3(position.x - 0.35f, position.y -0.75, 0.0f); // ���� ���� �Ʒ�
    rightLegOffset = glm::vec3(position.x +0.35f, position.y-0.75, 0.0f); // ���� ������ �Ʒ�
}

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

// ������ �Լ�
void Character::render(glm::vec3 lightPos, glm::vec3 viewPos) {
    // �� ��ȯ ��� ���� (���� ����)
    glm::mat4 baseModel = glm::mat4(1.0f);
    baseModel = glm::translate(baseModel, position);                // ���� ��ġ
    baseModel = glm::rotate(baseModel, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f)); // ���� ȸ��

    // ���� ������
    glm::mat4 bodyModel = glm::translate(baseModel, headOffset);
    drawCube(position + bodyOffset, bodySize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos);

    // �Ӹ� ������
    glm::mat4 headModel = glm::translate(baseModel, headOffset);
    drawCube(position + headOffset, headSize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos);

    // ���� ������
    glm::mat4 leftArmModel = glm::translate(baseModel, leftArmOffset);
    drawCube(position + leftArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos);

    // ������ ������
    glm::mat4 rightArmModel = glm::translate(baseModel, rightArmOffset);
    drawCube(position + rightArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos);

    // �޴ٸ� ������
    glm::mat4 leftLegModel = glm::translate(baseModel, leftLegOffset);
    drawCube(position + leftLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos);

    // �����ٸ� ������
    glm::mat4 rightLegModel = glm::translate(baseModel, rightLegOffset);
    drawCube(position + rightLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos);
}