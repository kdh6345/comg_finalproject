#include "common.h"
#include "globals.h"
#include "shaders.h"
#include "draw_cube.h"
#include "character.h"
#include "background.h"
#include "animation.h"

Character* character;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ĳ���� ������
    character->render(lightPos, viewPos);
  
    drawSun(shaderProgram);

    drawGround(shaderProgram);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': character->move(0.0f, 0.0f, -0.1f); break; // ������ �̵�
    case 's': character->move(0.0f, 0.0f, 0.1f); break;  // �ڷ� �̵�
    case 'a': character->move(-0.1f, 0.0f, 0.0f); break; // ���� �̵�
    case 'd': character->move(0.1f, 0.0f, 0.0f); break;  // ������ �̵�
    case 'q': character->rotate(-5.0f); break;           // ���� ȸ��
    case 'e': character->rotate(5.0f); break;            // ������ ȸ��
    default: break;
    }

    glutPostRedisplay();
}

void init() {
    // ���̴� ���α׷� ����
    shaderProgram = createShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

    // ť�� �ʱ�ȭ
    initCube();

    // ĳ���� ����
    character = new Character(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.5f, 0.8f, 0.2f));



    // OpenGL ���� ����
    glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Character Example");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    delete character;
    return 0;
}