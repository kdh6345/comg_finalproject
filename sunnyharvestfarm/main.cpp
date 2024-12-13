#include "common.h"
#include "globals.h"
#include "shaders.h"
#include "draw_cube.h"
#include "character.h"

Character* character;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::vec3 lightPos = glm::vec3(10.0f, 10.0f, 10.0f);
    glm::vec3 viewPos = glm::vec3(20.0f, 20.0f, 20.0f);

    // 캐릭터 렌더링
    character->render(lightPos, viewPos);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': character->move(0.0f, 0.0f, -0.1f); break; // 앞으로 이동
    case 's': character->move(0.0f, 0.0f, 0.1f); break;  // 뒤로 이동
    case 'a': character->move(-0.1f, 0.0f, 0.0f); break; // 왼쪽 이동
    case 'd': character->move(0.1f, 0.0f, 0.0f); break;  // 오른쪽 이동
    case 'q': character->rotate(-5.0f); break;           // 왼쪽 회전
    case 'e': character->rotate(5.0f); break;            // 오른쪽 회전
    default: break;
    }

    glutPostRedisplay();
}

void init() {
    // 쉐이더 프로그램 생성
    shaderProgram = createShaderProgram("vertex_shader.glsl", "fragment_shader.glsl");

    // 큐브 초기화
    initCube();

    // 캐릭터 생성
    character = new Character(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.5f, 0.8f, 0.2f));

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

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    delete character;
    return 0;
}