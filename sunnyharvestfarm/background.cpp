#include "common.h"
#include "globals.h"
#include "background.h"

// �ٴ��� �׸��� �Լ�
void drawGround(GLuint shaderProgram) {
    // �簢�� ���� ������ (XZ ���)
    float vertices[] = {
        // Positions           // Colors
        -ground_size, 0.0f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-left
         ground_size, 0.0f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-right
         ground_size, 0.0f,  ground_size,  0.3f, 0.6f, 0.3f, // Top-right
        -ground_size, 0.0f,  ground_size,  0.3f, 0.6f, 0.3f  // Top-left
    };

    // �簢�� �ε��� ������
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // VAO ����
    glBindVertexArray(VAO);

    // VBO�� ���� ������ ���ε�
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO�� �ε��� ������ ���ε�
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // ��ġ �Ӽ�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ���� �Ӽ�
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // �׸���
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // ����
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void drawSun(GLuint shaderProgram) {
    glUseProgram(shaderProgram); // ���̴� Ȱ��ȭ

    glPushMatrix();

    // �¾� ��ġ ����
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // ������ ��Ȱ��ȭ�Ͽ� �¾� ������
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // �¾� ����: ���� �����
    GLUquadric* quad = gluNewQuadric();
    gluSphere(quad, 0.5, 32, 32); // ������ 0.5, ���׸�Ʈ 32x32
    gluDeleteQuadric(quad);

    // ���� �ٽ� Ȱ��ȭ
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

