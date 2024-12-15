#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H

void drawGround(GLuint shaderProgram);
void drawSun(GLuint shaderProgram);
void drawCounter(GLuint shaderProgram); // Counter �߰�

class ChickenPlace {
public:
    ChickenPlace(glm::vec3 point1, glm::vec3 point2);

    void render(unsigned int shaderProgram);

private:
    glm::vec3 point1; // ù ��° ��
    glm::vec3 point2; // �� ��° ��
};

// ���� ���� �Լ�
void addPlatform(glm::vec3 position);
void renderPlatforms(float radius, GLuint shaderProgram);
void checkPlayerOnPlatform(glm::vec3 playerPosition, glm::vec3 playerSize, float platformRadius);

#endif