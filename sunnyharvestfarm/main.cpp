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
HoldingEgg* holdingEgg = nullptr; // ĳ���Ͱ� ��� �ִ� �ް�
std::vector<HoldingEgg> holdingEggs; // ĳ���Ͱ� ��� �ִ� �ް� ����
std::vector<Egg> chickenPlaceEggs; // ChickenPlace ������ �ް���
std::vector<DropEgg> dropEggs; // ī���� ���� �ִ� DropEgg ����Ʈ
std::vector<Customer> customers;   // �մ� ����Ʈ
float customerSpawnInterval = 10.0f; // �մ� ���� ���� (��)
float timeSinceLastCustomer = 0.0f; // ������ �մ� ���� �� ��� �ð�

ChickenPlace* chickenPlace;       // ChickenPlace ��ü
float eggGenerationInterval = 1.0f; // �ް� ���� ���� (��)
float timeSinceLastEgg = 0.0f;

// �߰�: �����ؾ� �� ���� �մ� ��
int remainingCustomersToSpawn = 0;

glm::vec3 generateRandomEggPosition(const glm::vec3& minPoint, const glm::vec3& maxPoint) {
float randomX = minPoint.x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxPoint.x - minPoint.x)));
float randomZ = minPoint.z + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (maxPoint.z - minPoint.z)));
return glm::vec3(randomX, minPoint.y, randomZ); // Y�� ����
}

// ���� �� �ް� ����
void addEggInChickenPlace() {
    if (chickenPlaceEggs.size() < 50) 
    {
        glm::vec3 minPoint = glm::vec3(-5.0f, 0.5f, -20.0f);
        glm::vec3 maxPoint = glm::vec3(5.0f, 0.5f, -10.0f);

        glm::vec3 eggPosition = generateRandomEggPosition(minPoint, maxPoint);
        chickenPlaceEggs.emplace_back(eggPosition, glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1.0f, 1.0f, 0.0f)); // ����� �ް�
    }
}
void spawnRandomCustomers(int value) {
    if (remainingCustomersToSpawn > 0) {
        // �մ� ����
        glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f);
        glm::vec3 size(1.0f, 1.0f, 0.5f);
        glm::vec3 color(0.9f, 0.5f, 0.2f);
        customers.emplace_back(spawnPosition, size, color);

        //std::cout << "[DEBUG] Spawned a customer. Remaining: " << (remainingCustomersToSpawn - 1) << std::endl;

        --remainingCustomersToSpawn;

        // 3�� �� ���� �մ� ����
        if (remainingCustomersToSpawn > 0) {
            glutTimerFunc(3000, spawnRandomCustomers, 0); // 3�� �� ��ȣ��
        }
    }
}

void startSpawningCustomers() {
    const int maxCustomers = 6; // �ִ� �մ� �� ����

    // ���� �մ� ���� �ִ� ���Ѻ��� ���� ��쿡�� ����
    if (customers.size() < maxCustomers) {
        remainingCustomersToSpawn = rand() % 5 + 1; // 1~5���� �մ� ����
        std::cout << "[DEBUG] Starting to spawn " << remainingCustomersToSpawn << " customers." << std::endl;

        spawnRandomCustomers(0); // ù ��° �մ� ��� ����
    }
    else {
        std::cout << "[DEBUG] Maximum customer limit reached. Waiting to spawn more." << std::endl;
    }
}


void stackEggOnCounter() 
{
    if (holdingEggs.empty()) return; // ��� �ִ� �ް��� ������ ����

// ī���� ��ġ�� �״� ���� ����
    glm::vec3 counterBasePosition = glm::vec3(0.0f, 1.0f, 1.5f); // ī���� ��ġ
    float eggStackOffset = 0.6f; // �� �ް� ���� Y�� ����

// ī���� ���� �̹� ���� �ް��� ������ Ȯ��
    int currentStackCount = dropEggs.size();

// HoldingEgg���� DropEgg�� �ϳ��� �̵�
    while (!holdingEggs.empty()) {
        glm::vec3 nextTargetPosition = counterBasePosition + glm::vec3(0.0f, currentStackCount * eggStackOffset, 0.0f);

        HoldingEgg topHoldingEgg = holdingEggs.back(); // ���� ���� HoldingEgg
        dropEggs.emplace_back(topHoldingEgg.getPosition(), nextTargetPosition, topHoldingEgg.getSize(), topHoldingEgg.getColor());

        holdingEggs.pop_back(); // HoldingEgg ����Ʈ���� ����
        ++currentStackCount;   // ���� ���� ����
    }
}

void spawnCustomers() {
    int numCustomers = rand() % 5 + 1; // 1 ~ 5�� ���� ���� �մ� ����
    float spacing = 2.0f;             // �� ����

    glm::vec3 basePosition(0.0f, 0.5f, 18.0f); // �� �� ���� ���� ��ġ

    for (int i = 0; i < numCustomers; ++i) {
        glm::vec3 customerPosition = basePosition + glm::vec3(0.0f, 0.0f, i * spacing);
        glm::vec3 customerSize = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 customerColor = glm::vec3(0.7f, 0.5f, 0.2f); // ��Ȳ��

        
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

    const int maxCustomers = 6; // �ִ� �մ� �� ����
    const float spacing = 2.0f; // �մ� �� �ּ� ����
    glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f); // �մ� ���� ��ġ
    std::vector<size_t> customersToRemove;

    for (size_t i = 0; i < customers.size(); ++i) {
        Customer& customer = customers[i];

        // ���� �մ��� ��ǥ ��ġ�� ���
        glm::vec3 targetPosition = customer.getTargetPosition();

        // �� �մ԰��� �Ÿ� Ȯ��
        if (i > 0) { // ù ��° �մ��� �տ� �մ��� ����
            const Customer& previousCustomer = customers[i - 1];
            float distanceToPrevious = glm::distance(customer.getPosition(), previousCustomer.getPosition());

            // �� �մ԰��� ������ ������ ����
            if (distanceToPrevious < spacing) {
                customer.stop();
                continue;
            }
        }

        // �մ��� ��ǥ ��ġ�� �����ߴ��� Ȯ��
        if (customer.isAtTarget()) {
            if (!customer.isCarryingEggsStatus()) {
                // ī���Ϳ� ���������� �ް��� ������ ���
                if (!dropEggs.empty()) {
                    customer.takeEggs(dropEggs); // �ް� ������
                }
             
            }
            else {
                glm::vec3 spawnPosition(0.0f, 0.5f, 18.0f); // ���� ��ġ
                if (glm::distance(customer.getPosition(), spawnPosition) < 0.5f) {
                    customersToRemove.push_back(i); // ���� ����
                }
            }
        }
        else {
            // �մ� �̵� �� �ִϸ��̼� ������Ʈ
            customer.updatePosition(deltaTime);
            customer.updateAnimation(deltaTime);
        }
    }

    // ������ �մ� ���� (�������� �����Ͽ� �ε��� ������ ����)
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

// AABB �浹 ����
bool collisionX = charPos.x + charSize.x >= eggPos.x - eggSize.x &&
charPos.x - charSize.x <= eggPos.x + eggSize.x;
bool collisionY = charPos.y + charSize.y >= eggPos.y - eggSize.y &&
charPos.y - charSize.y <= eggPos.y + eggSize.y;
bool collisionZ = charPos.z + charSize.z >= eggPos.z - eggSize.z &&
charPos.z - charSize.z <= eggPos.z + eggSize.z;

if (collisionX && collisionY && collisionZ) {
// ��ǥ ��ġ�� �Ӹ� �� + ���� ����
glm::vec3 newEggOffset(0.0f, 1.25f + holdingEggs.size() * 0.6f, 0.0f);

// HoldingEgg ���� (���� ��ġ�� �浹�� �ް��� ��ġ)
holdingEggs.emplace_back(eggPos, newEggOffset, eggSize, glm::vec3(1.0f, 1.0f, 0.0f));
continue; // �浹�� �ް��� ����
}

remainingEggs.push_back(egg);
}

chickenPlaceEggs = remainingEggs;
}

void display() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// ĳ���� ������
drawCounter(shaderProgram);
character->render(lightPos, viewPos);
drawSun(shaderProgram);
renderPlatforms(1.0f, shaderProgram);
drawGround(shaderProgram);
// ChickenPlace ������
chickenPlace->render(shaderProgram);
   

// �浹 ����
checkCollision();

// ��� Egg ������
for (const auto& egg : chickenPlaceEggs) {
egg.render(lightPos, viewPos);
}
// HoldingEgg ���� ��ġ ������Ʈ �� ������
glm::vec3 charHeadPosition = character->getPosition() + glm::vec3(0.0f, 1.25f, 0.0f);
for (auto& holdingEgg : holdingEggs) {
holdingEgg.updatePosition(charHeadPosition, 0.016f); // 16ms(60 FPS ����)
holdingEgg.render(lightPos, viewPos);
}
renderDropEggs(lightPos, viewPos);

// �մ� ������
renderCustomers(lightPos, viewPos);
// ���� ���

glutSwapBuffers();
}

void updateAnimation(int value) {
    float deltaTime = 0.016f; // 60 FPS ����

    // �մ� ���� �ֱ� ����
    timeSinceLastCustomer += deltaTime;
    if (timeSinceLastCustomer >= customerSpawnInterval) {
        timeSinceLastCustomer = 0.0f;
        startSpawningCustomers(); // ���� �մ� ���� ����
    }

    // ���� �ִϸ��̼� �� ������Ʈ ����
    updateCustomers(deltaTime);

    if (walking) {
        character->updateRotation(); // ĳ������ ȸ�� ������Ʈ
        updateDropEggs(deltaTime);   // DropEgg �ε巴�� �̵�

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

    if (dropping && !holdingEggs.empty()) {
        stackEggOnCounter();
    }
    // �÷��� �� Ȯ�� �� ī���ͷ� �ް� �̵�
    checkPlayerOnPlatform(character->getPosition(), character->getSize(), 1.0f);

    // DropEgg �ε巴�� �̵�
    updateDropEggs(deltaTime);

    // ChickenPlace �ް� ���� ����
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
    case 'a': // ���� ȸ��
        character->setTargetRotation(90.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 'd': // ������ ȸ��
        character->setTargetRotation(270.0f);
        character->move(0.0f, 0.0f, 0.3f, collisionManager);
        walking = true;
        break;
    case 'e': // ���ο� Egg �߰�
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
collisionManager.addCollisionObject(CollisionObject(glm::vec3(0.0f, 0.5f, 1.5f), glm::vec3(3.0f, 1.0f, 2.0f))); // Counter
character = new Character(glm::vec3(0.0f, 0.5f, -2.0f), glm::vec3(1.0f, 1.0f, 0.5f), glm::vec3(0.5f, 0.8f, 0.2f));
// ChickenPlace �ʱ�ȭ
chickenPlace = new ChickenPlace(glm::vec3(-5.0f, 0.0f, -20.0f), glm::vec3(5.0f, 0.0f, -10.0f));
addPlatform(glm::vec3(1.5f, 0.01f, -1.7f)); // ���� �߰�
    
// OpenGL ���� ����
glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0))); // ���� �ʱ�ȭ
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
