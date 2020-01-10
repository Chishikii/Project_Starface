#include "charactercontroller.h"
#include "inputregistry.h"

CharacterController::CharacterController(Player* playerCharacter) : IdleObserver()
{
    m_Timer.restart();
    this->playerCharacter = playerCharacter;
    v_PlayerPhysicsObject = playerCharacter->returnPlayerPhysObject();
}

void CharacterController::doIt()
{
    long long time = m_Timer.restart();

    //flag for direction
    unsigned long long v_MovementFlag = 0;
    QMatrix4x4 modelMatrix = v_PlayerPhysicsObject->getEngineModelMatrix();

    KeyboardInput* keyInput = InputRegistry::getInstance().getKeyboardInput();

    if (keyInput->isKeyPressed('w'))
    {
        v_MovementFlag |= MovementFlag::Forward;
    }
    if (keyInput->isKeyPressed('a'))
    {
        v_MovementFlag |= MovementFlag::SlowTurn;
        v_MovementFlag |= MovementFlag::TurnLeft;
    }
    if (keyInput->isKeyPressed('s'))
    {
        v_MovementFlag |= MovementFlag::Backward;
    }
    if (keyInput->isKeyPressed('d'))
    {
        v_MovementFlag |= MovementFlag::SlowTurn;
        v_MovementFlag |= MovementFlag::TurnRight;
    }
    if (keyInput->isKeyPressed('q'))
    {
        modelMatrix.rotate(10,QVector3D(0,0,1));
    }

    //character in entsprechende richtungen bewegen
    playerCharacter->returnPlayerCam()->moveCharacter(time, v_MovementFlag);
}
