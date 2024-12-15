#include "common.h"
#include "globals.h"
#include "background.h"
#include "draw_cube.h"

// ���� ����Ʈ
std::vector<glm::vec3> platforms;

// ���� �߰� �Լ�
void addPlatform(glm::vec3 position) {
    platforms.push_back(position);
}

void drawPlatformXZ(glm::vec3 position, float radius, GLuint shaderProgram) {
    // ���̴� ���α׷� Ȱ��ȭ
    glUseProgram(shaderProgram);

    // �� ��� ���� (��ġ �̵� �� ȸ��)
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position); // ��ġ�� �̵�
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)); // X�� ���� -90�� ȸ��

    // ���̴��� �� ��� ����
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // ���̴��� ���� ���� (������)
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, 1.0f, 0.0f, 0.0f, 1.0f); // RGBA: ������, ������

    // ���� ���� ����
    GLUquadric* quad = gluNewQuadric();
    gluDisk(quad, 0.0f, radius, 36, 1); // ������ ����, ���� 36
    gluDeleteQuadric(quad);
}

void renderPlatforms(float radius, GLuint shaderProgram) {
    for (const auto& position : platforms) {
        drawPlatformXZ(position, radius, shaderProgram); // ���̴� ���
    }
}


void checkPlayerOnPlatform(glm::vec3 playerPosition, glm::vec3 playerSize, float platformRadius) {
    dropping = false; // �⺻���� �������� ����

    for (const auto& platform : platforms) {
        float distanceX = std::abs(playerPosition.x - platform.x);
        float distanceZ = std::abs(playerPosition.z - platform.z);

        // �÷��� ���� �ִ��� Ȯ�� (�ܼ� ���� �浹)
        if (distanceX <= platformRadius + playerSize.x / 2 &&
            distanceZ <= platformRadius + playerSize.z / 2 &&
            playerPosition.y <= platform.y + 0.6f && // �÷��� ��
            playerPosition.y >= platform.y) {       // �÷��� �ٷ� ��
            dropping = true; // �÷��� ���� �����Ƿ� �������� ���� ����
            return;
        }
    }
}


// �ٴ��� �׸��� �Լ�
void drawGround(GLuint shaderProgram) {
    glUseProgram(shaderProgram);
    // ���� ���� ����
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, 0.3f, 0.6f, 0.3f, 1.0f); // ���

    // �簢�� ���� ������ (XZ ���)
    float vertices[] = {
        // Positions           // Colors
        -ground_size, -0.01f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-left
         ground_size, -0.01f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-right
         ground_size, -0.01f,  ground_size,  0.3f, 0.6f, 0.3f, // Top-right
        -ground_size, -0.01f,  ground_size,  0.3f, 0.6f, 0.3f  // Top-left
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

// Counter�� �׸��� �Լ�
void drawCounter(GLuint shaderProgram) {
    glUseProgram(shaderProgram);

    // ���� ���� ����
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, 0.2f, 0.8f, 0.8f, 0.5f); // û�ϻ�, ������

    // ���� Ȱ��ȭ (������)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // �� ��ȯ ���
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.5f, 1.5f)); // ��ġ ����
    model = glm::scale(model, glm::vec3(5.0f, 1.0f, 2.0f));     // ũ�� ����

    // Counter ���� �� ���� ����
    glm::vec3 color(0.2f, 0.6f, 0.8f); // û�ϻ�
    float transparency = 0.2f;         // ������

    // drawghostCube ȣ��
    drawCube(glm::vec3(0.0f, 0.5f, 1.5f), glm::vec3(5.0f, 1.0f, 2.0f), color, lightPos, viewPos, model);

    // ���� ����
    glDisable(GL_BLEND);
}

void drawSun(GLuint shaderProgram) {
    glUseProgram(shaderProgram);

    // ���� ���� ����
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, 1.0f,1.0f,0.0f,1.0f); // û�ϻ�, ������

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

ChickenPlace::ChickenPlace(glm::vec3 point1, glm::vec3 point2)
    : point1(point1), point2(point2) {}

void ChickenPlace::render(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    // ���� ����
    glm::vec3 color(0.5f, 0.8f, 0.5f); // ���� ���
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, color.r, color.g, color.b, 1.0f);

    // ������ �߽� ���
    glm::vec3 center = glm::vec3(
        (point1.x + point2.x) / 2.0f,
        (point1.y + point2.y) / 2.0f,
        (point1.z + point2.z) / 2.0f
    );

    // ������ ũ�� ���
    glm::vec3 size = glm::vec3(
        std::abs(point2.x - point1.x),
        std::abs(point2.y - point1.y),
        std::abs(point2.z - point1.z)
    );

    // ���� �� �� ��ȯ ��� ����
   
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, center);
    model = glm::scale(model, size);

    // `drawCube` ȣ��� ���� ������
    drawCube(center, size, color, lightPos, viewPos, model);
}

secondPlace::secondPlace(glm::vec3 point1, glm::vec3 point2)
    : point1(point1), point2(point2) {}

void secondPlace::render(unsigned int shaderProgram) {
    glUseProgram(shaderProgram);
    // ���� ����
    glm::vec3 color(0.0f, 0.0f, 1.0f); // ���� ���
    GLuint colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
    glUniform4f(colorLoc, color.r, color.g, color.b, 1.0f);

    // ������ �߽� ���
    glm::vec3 center = glm::vec3(
        (point1.x + point2.x) / 2.0f,
        (point1.y + point2.y) / 2.0f,
        (point1.z + point2.z) / 2.0f
    );

    // ������ ũ�� ���
    glm::vec3 size = glm::vec3(
        std::abs(point2.x - point1.x),
        std::abs(point2.y - point1.y),
        std::abs(point2.z - point1.z)
    );

    // ���� �� �� ��ȯ ��� ����

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, center);
    model = glm::scale(model, size);

    // `drawCube` ȣ��� ���� ������
    drawCube(center, size, color, lightPos, viewPos, model);
}

