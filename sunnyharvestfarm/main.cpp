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
    case 'w':
        character->setTargetRotation(180.0f);
        character->move(0.0f, 0.0f, 0.1f);
        walking = true;
        break;
    case 's':
        character->setTargetRotation(0.0f);
        character->move(0.0f, 0.0f, 0.1f);
        walking = true;
        break;
    case 'a': // ���� ȸ��
        character->setTargetRotation(90.0f);
        character->move(0.0f, 0.0f, 0.1f); // ȸ�� ������ ���� ���� �̵�
        walking = true;
        break;
    case 'd': // ������ ȸ��
        character->setTargetRotation(270.0f);
        character->move(0.0f, 0.0f, 0.1f); // ȸ�� ������ ���� ������ �̵�
        walking = true;
        break;
    default:
        walking = false;
        break;
    }

    glutPostRedisplay();
}
void updateAnimation(int value) {
    if (walking) {
        character->updateRotation(); // ĳ������ ȸ�� ������Ʈ

        // ���� ���� ����
        float swingSpeed = 5.0f;
        if (swingDirection) {
            leftArmSwing += swingSpeed;
            rightArmSwing -= swingSpeed;
            leftLegSwing -= swingSpeed;
            rightLegSwing += swingSpeed;
        }
        else {
            leftArmSwing -= swingSpeed;
            rightArmSwing += swingSpeed;
            leftLegSwing += swingSpeed;
            rightLegSwing -= swingSpeed;
        }

        if (leftArmSwing >= 50.0f || leftArmSwing <= -50.0f) {
            swingDirection = !swingDirection;
        }
    }
    else {
        leftArmSwing *= 0.9f;
        rightArmSwing *= 0.9f;
        leftLegSwing *= 0.9f;
        rightLegSwing *= 0.9f;

        if (std::abs(leftArmSwing) < 1.0f) leftArmSwing = 0.0f;
        if (std::abs(rightArmSwing) < 1.0f) rightArmSwing = 0.0f;
        if (std::abs(leftLegSwing) < 1.0f) leftLegSwing = 0.0f;
        if (std::abs(rightLegSwing) < 1.0f) rightLegSwing = 0.0f;
    }

    glutTimerFunc(16, updateAnimation, 0); // 60 FPS
    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y) {
    // �ȱ� Ű�� ���� �� walking�� false�� ����
    switch (key) {
    case 'w':
    case 's':
    case 'a':
    case 'd':
        walking = false; // �ȴ� ���� ��Ȱ��ȭ
        break;
    default:
        break;
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

    glutTimerFunc(16, updateAnimation, 0);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMainLoop();

    delete character;
    return 0;
}