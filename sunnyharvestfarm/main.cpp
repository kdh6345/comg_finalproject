#include "common.h"
#include "globals.h"
#include "shaders.h"
#include "draw_cube.h"
#include "character.h"
#include "background.h"
#include "animation.h"
#include "item.h"
#include "customer.h"

CollisionManager collisionManager;
Character* character;
HoldingEgg* holdingEgg = nullptr; // 캐릭터가 들고 있는 달걀
std::vector<HoldingEgg> holdingEggs; // 캐릭터가 들고 있는 달걀 스택
std::vector<Egg> chickenPlaceEggs; // ChickenPlace 내부의 달걀들
std::vector<DropEgg> dropEggs; // 카운터 위에 있는 DropEgg 리스트
std::vector<Customer> customers;   // 손님 리스트
float customerSpawnInterval = 10.0f; // 손님 생성 간격 (초)
float timeSinceLastCustomer = 0.0f; // 마지막 손님 생성 후 경과 시간

ChickenPlace* chickenPlace;       // ChickenPlace 객체
float eggGenerationInterval = 1.0f; // 달걀 생성 간격 (초)
float timeSinceLastEgg = 0.0f;

// 추가: 생성해야 할 남은 손님 수
int remainingCustomersToSpawn = 0;

glm::vec3 generateRandomEggPosition(const glm::vec3& minPoint, const glm::vec3& maxPoint) {
float randomX = minPoint.x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxPoint.x - minPoint.x)));
float randomZ = minPoint.z + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxPoint.z - minPoint.z)));
return glm::vec3(randomX, minPoint.y, randomZ); // Y는 고정
}

// 영역 내 달걀 생성
void addEggInChickenPlace() {
    if (chickenPlaceEggs.size() < 50) 
    {
        glm::vec3 minPoint = glm::vec3(-5.0f, 0.5f, -20.0f);
        glm::vec3 maxPoint = glm::vec3(5.0f, 0.5f, -10.0f);

        glm::vec3 eggPosition = generateRandomEggPosition(minPoint, maxPoint);
        chickenPlaceEggs.emplace_back(eggPosition, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)); // 노란색 달걀
    }
}
void spawnRandomCustomers(int value) {
    if (remainingCustomersToSpawn > 0) {
        // 손님 생성
        glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f);
        glm::vec3 size(1.0f, 1.0f, 0.5f);
        glm::vec3 color(0.9f, 0.5f, 0.2f);
        customers.emplace_back(spawnPosition, size, color);

        //std::cout << "[DEBUG] Spawned a customer. Remaining: " << (remainingCustomersToSpawn - 1) << std::endl;

        --remainingCustomersToSpawn;

        // 3초 후 다음 손님 생성
        if (remainingCustomersToSpawn > 0) {
            glutTimerFunc(3000, spawnRandomCustomers, 0); // 3초 후 재호출
        }
    }
}

void startSpawningCustomers() {
    const int maxCustomers = 6; // 최대 손님 수 제한

    // 현재 손님 수가 최대 제한보다 작을 경우에만 생성
    if (customers.size() < maxCustomers) {
        remainingCustomersToSpawn = rand() % 5 + 1; // 1~5명의 손님 설정
        std::cout << "[DEBUG] Starting to spawn " << remainingCustomersToSpawn << " customers." << std::endl;

        spawnRandomCustomers(0); // 첫 번째 손님 즉시 생성
    }
    else {
        std::cout << "[DEBUG] Maximum customer limit reached. Waiting to spawn more." << std::endl;
    }
}


void stackEggOnCounter() 
{
    if (holdingEggs.empty()) return; // 들고 있는 달걀이 없으면 종료

// 카운터 위치와 쌓는 간격 설정
    glm::vec3 counterBasePosition = glm::vec3(0.0f, 1.0f, 1.5f); // 카운터 위치
    float eggStackOffset = 0.6f; // 각 달걀 간의 Y축 간격

// 카운터 위에 이미 쌓인 달걀의 개수를 확인
    int currentStackCount = dropEggs.size();

// HoldingEgg에서 DropEgg로 하나씩 이동
    while (!holdingEggs.empty()) {
        glm::vec3 nextTargetPosition = counterBasePosition + glm::vec3(0.0f, currentStackCount * eggStackOffset, 0.0f);

        HoldingEgg topHoldingEgg = holdingEggs.back(); // 가장 위의 HoldingEgg
        dropEggs.emplace_back(topHoldingEgg.getPosition(), nextTargetPosition, topHoldingEgg.getSize(), topHoldingEgg.getColor());

        holdingEggs.pop_back(); // HoldingEgg 리스트에서 제거
        ++currentStackCount;   // 쌓인 개수 증가
    }
}

void spawnCustomers() {
    int numCustomers = rand() % 5 + 1; // 1 ~ 5명 사이 랜덤 손님 생성
    float spacing = 2.0f;             // 줄 간격

    glm::vec3 basePosition(0.0f, 0.5f, 18.0f); // 줄 맨 앞의 기준 위치

    for (int i = 0; i < numCustomers; ++i) {
        glm::vec3 customerPosition = basePosition + glm::vec3(0.0f, 0.0f, i * spacing);
        glm::vec3 customerSize = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 customerColor = glm::vec3(0.7f, 0.5f, 0.2f); // 주황색

        
        customers.emplace_back(customerPosition, customerSize, customerColor);
    }
}


void renderCustomers(glm::vec3 lightPos, glm::vec3 viewPos) {
for (const auto& customer : customers) 
    {
    customer.render(lightPos, viewPos);
    }
}
void updateCustomers(float deltaTime) {

    const int maxCustomers = 6; // 최대 손님 수 제한
    const float spacing = 2.0f; // 손님 간 최소 간격
    glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f); // 손님 스폰 위치
    std::vector<size_t> customersToRemove;

    for (size_t i = 0; i < customers.size(); ++i) {
        Customer& customer = customers[i];

        // 현재 손님의 목표 위치를 계산
        glm::vec3 targetPosition = customer.getTargetPosition();

        // 앞 손님과의 거리 확인
        if (i > 0) { // 첫 번째 손님은 앞에 손님이 없음
            const Customer& previousCustomer = customers[i - 1];
            float distanceToPrevious = glm::distance(customer.getPosition(), previousCustomer.getPosition());

            // 앞 손님과의 간격이 좁으면 멈춤
            if (distanceToPrevious < spacing) {
                customer.stop();
                continue;
            }
        }

        // 손님이 목표 위치에 도달했는지 확인
        if (customer.isAtTarget()) {
            if (!customer.isCarryingEggsStatus()) {
                // 카운터에 도착했으나 달걀이 없으면 대기
                if (!dropEggs.empty()) {
                    customer.takeEggs(dropEggs); // 달걀 가져감
                }
             
            }
            else {
                glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f); // 스폰 위치
                if (glm::distance(customer.getPosition(), spawnPosition) < 0.5f) {
                    customersToRemove.push_back(i); // 삭제 예정
                }
            }
        }
        else {
            // 손님 이동 및 애니메이션 업데이트
            customer.updatePosition(deltaTime);
            customer.updateAnimation(deltaTime);
        }
    }

    // 삭제할 손님 제거 (역순으로 삭제하여 인덱스 안정성 유지)
    for (auto it = customersToRemove.rbegin(); it != customersToRemove.rend(); ++it) {
        std::cout << "[DEBUG] Removing customer at index: " << *it << std::endl;
        customers.erase(customers.begin() + *it);
    }
}



void checkCollision() {
glm::vec3 charPos = character->getPosition();
glm::vec3 charSize = character->getSize();

std::vector<Egg> remainingEggs;

for (const auto& egg : chickenPlaceEggs) {
glm::vec3 eggPos = egg.getPosition();
glm::vec3 eggSize = egg.getSize();

// AABB 충돌 감지
bool collisionX = charPos.x + charSize.x >= eggPos.x - eggSize.x &&
charPos.x - charSize.x <= eggPos.x + eggSize.x;
bool collisionY = charPos.y + charSize.y >= eggPos.y - eggSize.y &&
charPos.y - charSize.y <= eggPos.y + eggSize.y;
bool collisionZ = charPos.z + charSize.z >= eggPos.z - eggSize.z &&
charPos.z - charSize.z <= eggPos.z + eggSize.z;

if (collisionX && collisionY && collisionZ) {
// 목표 위치는 머리 위 + 스택 높이
glm::vec3 newEggOffset(0.0f, 1.25f + holdingEggs.size() * 0.6f, 0.0f);

// HoldingEgg 생성 (시작 위치는 충돌한 달걀의 위치)
holdingEggs.emplace_back(eggPos, newEggOffset, eggSize, glm::vec3(1.0f, 1.0f, 0.0f));
continue; // 충돌한 달걀은 삭제
}

remainingEggs.push_back(egg);
}

chickenPlaceEggs = remainingEggs;
}

void display() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// 캐릭터 렌더링
drawCounter(shaderProgram);
character->render(lightPos, viewPos);
drawSun(shaderProgram);
renderPlatforms(1.0f, shaderProgram);
drawGround(shaderProgram);
// ChickenPlace 렌더링
chickenPlace->render(shaderProgram);
   

// 충돌 감지
checkCollision();

// 모든 Egg 렌더링
for (const auto& egg : chickenPlaceEggs) {
egg.render(lightPos, viewPos);
}
// HoldingEgg 스택 위치 업데이트 및 렌더링
glm::vec3 charHeadPosition = character->getPosition() + glm::vec3(0.0f, 1.25f, 0.0f);
for (auto& holdingEgg : holdingEggs) {
holdingEgg.updatePosition(charHeadPosition, 0.016f); // 16ms(60 FPS 기준)
holdingEgg.render(lightPos, viewPos);
}
renderDropEggs(lightPos, viewPos);

// 손님 렌더링
renderCustomers(lightPos, viewPos);
// 코인 출력

glutSwapBuffers();
}

void updateAnimation(int value) {
    float deltaTime = 0.016f; // 60 FPS 기준

    // 손님 생성 주기 관리
    timeSinceLastCustomer += deltaTime;
    if (timeSinceLastCustomer >= customerSpawnInterval) {
        timeSinceLastCustomer = 0.0f;
        startSpawningCustomers(); // 랜덤 손님 생성 시작
    }

    // 기존 애니메이션 및 업데이트 로직
    updateCustomers(deltaTime);

    if (walking) {
        character->updateRotation(); // 캐릭터의 회전 업데이트
        updateDropEggs(deltaTime);   // DropEgg 부드럽게 이동

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

    if (dropping && !holdingEggs.empty()) {
        stackEggOnCounter();
    }
    // 플랫폼 위 확인 및 카운터로 달걀 이동
    checkPlayerOnPlatform(character->getPosition(), character->getSize(), 1.0f);

    // DropEgg 부드럽게 이동
    updateDropEggs(deltaTime);

    // ChickenPlace 달걀 생성 관리
    timeSinceLastEgg += deltaTime;
    if (timeSinceLastEgg >= eggGenerationInterval) {
        timeSinceLastEgg = 0.0f;
        addEggInChickenPlace();
    }

    glutTimerFunc(16, updateAnimation, 0); // 60 FPS
    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        character->setTargetRotation(180.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 's':
        character->setTargetRotation(0.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 'a': // 왼쪽 회전
        character->setTargetRotation(90.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 'd': // 오른쪽 회전
        character->setTargetRotation(270.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 'e': // 새로운 Egg 추가
        for (int i = chickenPlaceEggs.size(); i < 50; ++i) {
            addEggInChickenPlace();
        }
        break;
    default:
        walking = false;
        break;
    }

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
collisionManager.addCollisionObject(CollisionObject(glm::vec3(0.0f, 0.5f, 1.5f), glm::vec3(3.0f, 1.0f, 2.0f))); // Counter
character = new Character(glm::vec3(0.0f, 0.5f, -2.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.5f, 0.8f, 0.2f));
// ChickenPlace 초기화
chickenPlace = new ChickenPlace(glm::vec3(-5.0f, 0.0f, -20.0f), glm::vec3(5.0f, 0.0f, -10.0f));
addPlatform(glm::vec3(1.5f, 0.01f, -1.7f)); // 발판 추가
    
// OpenGL 상태 설정
glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0))); // 난수 초기화
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
