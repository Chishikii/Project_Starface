#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "idleobserver.h"
#include "physics.h"
#include "modeltransformation.h"
#include <QElapsedTimer>

//Class to control character
class CharacterController : public IdleObserver
{
public:
    CharacterController(DynamicCharacterWithCam* character, ModelTransformation* characterTransformation);
    void doIt();

private:
    DynamicCharacterWithCam* m_Character;
    ModelTransformation* m_CharacterTransformation;

    //better deltatime
    QElapsedTimer m_Timer;
};

#endif // CHARACTERCONTROLLER_H
