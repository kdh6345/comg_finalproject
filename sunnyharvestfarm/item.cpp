#include "item.h"
#include "globals.h"
#include "common.h"

// 생성자
Egg::Egg(glm::vec3 position, glm::vec3 size, glm::vec3 color)
    : position(position), size(size), color(color) {}

// 렌더링 함수
void Egg::render(glm::vec3 lightPos, glm::vec3 viewPos) const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, size);
    drawCube(position, size, color, lightPos, viewPos, model);
}

// 위치 반환
glm::vec3 Egg::getPosition() const {
    return position;
}

// 크기 반환
glm::vec3 Egg::getSize() const {
    return size;
}

glm::vec3 Egg::getColor() const {
    return color;
}






// HoldingEgg 클래스
HoldingEgg::HoldingEgg(glm::vec3 startPosition, glm::vec3 targetOffset, glm::vec3 size, glm::vec3 color)
    : currentPosition(startPosition), targetOffset(targetOffset), size(size), color(color) {}

void HoldingEgg::updatePosition(glm::vec3 basePosition, float deltaTime) {
    glm::vec3 targetPosition = basePosition + targetOffset;
    currentPosition = glm::mix(currentPosition, targetPosition, deltaTime * 5.0f); // 부드럽게 이동
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
    return color; // 색상 반환
}





// DropEgg 클래스
DropEgg::DropEgg(glm::vec3 startPosition, glm::vec3 targetPosition, glm::vec3 size, glm::vec3 color)
    : currentPosition(startPosition), targetPosition(targetPosition), size(size), color(color) {}

void DropEgg::updatePosition(float deltaTime) {
    currentPosition = glm::mix(currentPosition, targetPosition, deltaTime * 5.0f); // 부드럽게 이동
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

// DropEgg 리스트 관리
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
