#ifndef PLAYER_H
#define PLAYER_H

#include "drawable.h"
#include "texture.h"
#include "modeltransformation.h"

//! The Player class which contains all elements of the player and handles creation
class Player
{
public:

    Player();
private:
    //!PlayerModel currently only Fighter
    Drawable *v_PlayerModel;
    //!Camera for the Player
    DynamicCharacterWithCam *v_PlayerCharacter;
    //!Texture for the PlayerModel
    Texture *v_Texture;
    //!reference to a shader for texture
    Shader *s_TextureShader;
    //!Transformation for the playerModel
    ModelTransformation *t_PlayerTransformaton;
    //!PhysicConstructionInfo for the player physic Object
    PhysicObjectConstructionInfo *v_PlayerPhyObjConstInfo;
};

#endif // PLAYER_H
