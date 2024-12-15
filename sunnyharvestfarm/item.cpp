#include "item.h"
#include "globals.h"
#include "common.h"

// ������
Egg::Egg(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color) {}

// ������ �Լ�
void Egg::render(glm::vec3 lightPos, glm::vec3 viewPos) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    drawCube(position, size, color, lightPos, viewPos, model);
}

// ��ġ ��ȯ
glm::vec3 Egg::getPosition() const {
    return position;
}

// ũ�� ��ȯ
glm::vec3 Egg::getSize() const {
    return size;
}

glm::vec3 Egg::getColor() const {
    return color;
}






// HoldingEgg Ŭ����
HoldingEgg::HoldingEgg(glm::vec3 startPosition, glm::vec3 targetOffset, glm::vec3 size, glm::vec3 color)
    : currentPosition(startPosition), targetOffset(targetOffset), size(size), color(color) {}

void HoldingEgg::updatePosition(glm::vec3 basePosition, float deltaTime) {
    glm::vec3 targetPosition = basePosition + targetOffset;
    currentPosition = glm::mix(currentPosition, targetPosition, deltaTime * 5.0f); // �ε巴�� �̵�
}

void HoldingEgg::render(glm::vec3 lightPos, glm::vec3 viewPos) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, currentPosition);
    model = glm::scale(model, size);
    drawCube(currentPosition, size, color, lightPos, viewPos, model);
}
glm::vec3 HoldingEgg::getPosition() const {
    return currentPosition;
}
glm::vec3 HoldingEgg::getCurrentPosition() const {
    return currentPosition;
}

glm::vec3 HoldingEgg::getSize() const {
    return size;
}

glm::vec3 HoldingEgg::getColor() const {
    return color; // ���� ��ȯ
}





// DropEgg Ŭ����
DropEgg::DropEgg(glm::vec3 startPosition, glm::vec3 targetPosition, glm::vec3 size, glm::vec3 color)
    : currentPosition(startPosition), targetPosition(targetPosition), size(size), color(color) {}

void DropEgg::updatePosition(float deltaTime) {
    currentPosition = glm::mix(currentPosition, targetPosition, deltaTime * 5.0f); // �ε巴�� �̵�
}

void DropEgg::render(glm::vec3 lightPos, glm::vec3 viewPos) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, currentPosition);
    model = glm::scale(model, size);
    drawCube(currentPosition, size, color, lightPos, viewPos, model);
}

bool DropEgg::isAtTarget() const {
    return glm::distance(currentPosition, targetPosition) < 0.01f;
}
void DropEgg::renderAtPosition(glm::vec3 position, glm::vec3 lightPos, glm::vec3 viewPos) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    drawCube(position, size, color, lightPos, viewPos, model);
}

// DropEgg ����Ʈ ����
extern std::vector<DropEgg> dropEggs;

void addDropEgg(glm::vec3 startPosition, glm::vec3 targetPosition, glm::vec3 size, glm::vec3 color) {
    dropEggs.emplace_back(startPosition, targetPosition, size, color);
}

void updateDropEggs(float deltaTime) {
    for (auto& dropEgg : dropEggs) {
        dropEgg.updatePosition(deltaTime);
    }
    //dropEggs.erase(
    //    std::remove_if(dropEggs.begin(), dropEggs.end(),
    //        [](const DropEgg& egg) { return egg.isAtTarget(); }),
    //    dropEggs.end());
}

void renderDropEggs(glm::vec3 lightPos, glm::vec3 viewPos) {
    for (const auto& dropEgg : dropEggs) {
        dropEgg.render(lightPos, viewPos);
    }
}
