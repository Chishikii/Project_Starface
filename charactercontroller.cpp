#include "charactercontroller.h"
#include "inputregistry.h"

CharacterController::CharacterController(DynamicCharacterWithCam* character, ModelTransformation* characterTransformation) : IdleObserver()
{
    m_Character = character;
    m_Timer.restart();
}

void CharacterController::doIt()
{
    long long time = m_Timer.restart();

    //flag for direction
    unsigned long long v_MovementFlag = 0;

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


    //character in entsprechende richtungen bewegen
    m_Character->moveCharacter(time, v_MovementFlag);
}
