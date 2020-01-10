#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include "idleobserver.h"
#include "physics.h"
#include "modeltransformation.h"
#include "player.h"
#include <QElapsedTimer>

//Class to control character
class CharacterController : public IdleObserver
{
public:
    CharacterController(Player* playerCharacter);
    void doIt();

private:
    Player* playerCharacter;
    PhysicObject* v_PlayerPhysicsObject;
    QElapsedTimer m_Timer;
};

#endif // CHARACTERCONTROLLER_H
