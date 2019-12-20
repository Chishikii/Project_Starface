#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "idleobserver.h"
#include "physics.h"
#include <QElapsedTimer>

//Class to control character
class CharacterController : public IdleObserver
{
public:
    CharacterController(DynamicCharacterWithCam* character);
    void doIt();

private:
    DynamicCharacterWithCam* m_Character;

    //better deltatime
    QElapsedTimer m_Timer;
};

#endif // CHARACTERCONTROLLER_H
