#include "common.h"
#include "globals.h"
#include "background.h"

// 바닥을 그리는 함수
void drawGround(GLuint shaderProgram) {
    // 사각형 정점 데이터 (XZ 평면)
    float vertices[] = {
        // Positions           // Colors
        -ground_size, 0.0f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-left
         ground_size, 0.0f, -ground_size,  0.3f, 0.6f, 0.3f, // Bottom-right
         ground_size, 0.0f,  ground_size,  0.3f, 0.6f, 0.3f, // Top-right
        -ground_size, 0.0f,  ground_size,  0.3f, 0.6f, 0.3f  // Top-left
    };

    // 사각형 인덱스 데이터
    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // VAO 설정
    glBindVertexArray(VAO);

    // VBO에 정점 데이터 바인딩
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // EBO에 인덱스 데이터 바인딩
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 위치 속성
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 색상 속성
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    // 그리기
    glUseProgram(shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // 정리
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void drawSun(GLuint shaderProgram) {
    glUseProgram(shaderProgram); // 쉐이더 활성화

    glPushMatrix();

    // 태양 위치 설정
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, lightPos);
    GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // 조명을 비활성화하여 태양 렌더링
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.0f); // 태양 색상: 밝은 노란색
    GLUquadric* quad = gluNewQuadric();
    gluSphere(quad, 0.5, 32, 32); // 반지름 0.5, 세그먼트 32x32
    gluDeleteQuadric(quad);

    // 조명 다시 활성화
    glEnable(GL_LIGHTING);

    glPopMatrix();
}

