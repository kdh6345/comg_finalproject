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

    // 캐릭터 렌더링
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
    case 'a': // 왼쪽 회전
        character->setTargetRotation(90.0f);
        character->move(0.0f, 0.0f, 0.1f); // 회전 각도에 따라 왼쪽 이동
        walking = true;
        break;
    case 'd': // 오른쪽 회전
        character->setTargetRotation(270.0f);
        character->move(0.0f, 0.0f, 0.1f); // 회전 각도에 따라 오른쪽 이동
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
        character->updateRotation(); // 캐릭터의 회전 업데이트

        // 기존 스윙 로직
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
    // 걷기 키를 뗐을 때 walking을 false로 설정
    switch (key) {
    case 'w':
    case 's':
    case 'a':
    case 'd':
        walking = false; // 걷는 상태 비활성화
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

void init() {
    // 쉐이더 프로그램 생성
    shaderProgram = createShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

    // 큐브 초기화
    initCube();
   
    // 캐릭터 생성
    character = new Character(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.5f, 0.8f, 0.2f));



    // OpenGL 상태 설정
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