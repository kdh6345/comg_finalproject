#include "globals.h"
#include <cmath>
#include "animation.h"

// �¾��� ���� ���� ����
float lightOrbitRadius = 10.0f; // ���� �ݰ�
float lightAngle = 0.0f;        // ���� ����

// �¾��� ��ġ ������Ʈ
void updateSunPosition() {
    lightAngle += 0.01f; // ���� �ӵ�
    if (lightAngle > 360.0f) lightAngle -= 360.0f;

    // lightPos�� ���� ��η� ����
    lightPos.x = lightOrbitRadius * std::cos(lightAngle);
    lightPos.z = lightOrbitRadius * std::sin(lightAngle);
    lightPos.y = 10.0f; // Y�� ����
}
