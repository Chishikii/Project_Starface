#include "charactercontroller.h"
#include "inputregistry.h"

CharacterController::CharacterController(DynamicCharacterWithCam* character) : IdleObserver()
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
        v_MovementFlag |= MovementFlag::TurnLeft;
    }
    if (keyInput->isKeyPressed('s'))
    {
        v_MovementFlag |= MovementFlag::Backward;
    }
    if (keyInput->isKeyPressed('d'))
    {
        v_MovementFlag |= MovementFlag::TurnRight;
    }
    if (keyInput->isKeyPressed(Qt::Key_Space))
    {
        // momentan geht jump immer, vielleicht sollte man dort wo man springen soll einen trigger platzieren
        // und dann das movement flag setzen wenn man hineinläuft und den callback abarbeitet
        v_MovementFlag |= MovementFlag::Jump;
    }
    // character in entsprechende richtungen bewegen
    m_Character->moveCharacter(time, v_MovementFlag);
}
