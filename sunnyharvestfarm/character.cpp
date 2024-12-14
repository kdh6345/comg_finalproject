#include "character.h"

// ������: ����� �� ������ ����� ��ġ �� ũ�� �ʱ�ȭ
Character::Character(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color), rotationY(0.0f), targetRotationY(0.0f) {

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
    // ���� ȸ�� ������ �������� ��ȯ
    float radians = glm::radians(rotationY);

    // �̵� ���� ��� (ȸ�� ������ ���� x, z �� �̵�)
    position.x += dx * cos(radians) - dz * sin(radians);
    position.z += dx * sin(radians) + dz * cos(radians);
    position.y += dy; // y�� �̵��� �״��
}


void Character::setTargetRotation(float angle) {
    targetRotationY = angle;
}

void Character::updateRotation() {
    float rotationSpeed = 10.0f; // ȸ�� �ӵ�
    if (std::abs(rotationY - targetRotationY) > 0.1f) {
        // ������ ��ǥ ������ �̵�
        rotationY += (targetRotationY - rotationY) * 0.2f;
    }
    else {
        rotationY = targetRotationY; // ��ǥ ������ �����ϸ� ����
    }
}

void Character::render(glm::vec3 lightPos, glm::vec3 viewPos) {
    // �� ��ȯ ��� ���� (���� ����)
    glm::mat4 baseModel = glm::mat4(1.0f);
    baseModel = glm::translate(baseModel, position);
    baseModel = glm::rotate(baseModel, glm::radians(rotationY), glm::vec3(0.0f, 1.0f, 0.0f));

    // ���� ������
    glm::mat4 bodyModel = glm::translate(baseModel, bodyOffset);
    bodyModel = glm::scale(bodyModel, bodySize);
    drawCube(position + bodyOffset, bodySize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos, bodyModel);

    // �Ӹ� ������
    glm::mat4 headModel = glm::translate(baseModel, headOffset);
    headModel = glm::scale(headModel, headSize);
    drawCube(position + headOffset, headSize, glm::vec3(0.8f, 0.8f, 0.8f), lightPos, viewPos, headModel);

    // ���� ������
    glm::mat4 leftArmModel = glm::translate(baseModel, leftArmOffset);
    leftArmModel = glm::translate(leftArmModel, glm::vec3(0.0f, +armSize.y / 2.0f, 0.0f)); // ȸ���� �̵�
    leftArmModel = glm::rotate(leftArmModel, glm::radians(leftArmSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    leftArmModel = glm::translate(leftArmModel, glm::vec3(0.0f, -armSize.y / 2.0f, 0.0f)); // ȸ���� ����
    leftArmModel = glm::scale(leftArmModel, armSize);
    drawCube(position + leftArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos, leftArmModel);

    // ������ ������
    glm::mat4 rightArmModel = glm::translate(baseModel, rightArmOffset);
    rightArmModel = glm::translate(rightArmModel, glm::vec3(0.0f, armSize.y / 2.0f, 0.0f)); // ȸ���� �̵�
    rightArmModel = glm::rotate(rightArmModel, glm::radians(rightArmSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    rightArmModel = glm::translate(rightArmModel, glm::vec3(0.0f, -armSize.y / 2.0f, 0.0f)); // ȸ���� ����
    rightArmModel = glm::scale(rightArmModel, armSize);
    drawCube(position + rightArmOffset, armSize, glm::vec3(0.6f, 0.6f, 0.8f), lightPos, viewPos, rightArmModel);

    // �޴ٸ� ������
    glm::mat4 leftLegModel = glm::translate(baseModel, leftLegOffset);
    leftLegModel = glm::translate(leftLegModel, glm::vec3(0.0f, legSize.y / 2.0f, 0.0f)); // ȸ���� �̵�
    leftLegModel = glm::rotate(leftLegModel, glm::radians(leftLegSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    leftLegModel = glm::translate(leftLegModel, glm::vec3(0.0f, -legSize.y / 2.0f, 0.0f)); // ȸ���� ����
    leftLegModel = glm::scale(leftLegModel, legSize);
    drawCube(position + leftLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos, leftLegModel);

    // �����ٸ� ������
    glm::mat4 rightLegModel = glm::translate(baseModel, rightLegOffset);
    rightLegModel = glm::translate(rightLegModel, glm::vec3(0.0f, +legSize.y / 2.0f, 0.0f)); // ȸ���� �̵�
    rightLegModel = glm::rotate(rightLegModel, glm::radians(rightLegSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    rightLegModel = glm::translate(rightLegModel, glm::vec3(0.0f, -legSize.y / 2.0f, 0.0f)); // ȸ���� ����
    rightLegModel = glm::scale(rightLegModel, legSize);
    drawCube(position + rightLegOffset, legSize, glm::vec3(0.4f, 0.4f, 0.6f), lightPos, viewPos, rightLegModel);
}


