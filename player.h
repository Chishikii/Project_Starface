#ifndef PLAYER_H
#define PLAYER_H

#include "drawable.h"
#include "texture.h"
#include "modeltransformation.h"
#include "trianglemesh.h"
#include "physicaccessablecamera.h"
#include "scenemanager.h"

//! The Player class which contains all elements of the player and handles creation
class Player
{
public:

    Player();
    //!Input vertex info and texture as path and set shader aswell as Physic Engine
    Player(QString playerMeshObj, QString playerTexture, Shader* textureShader, PhysicEngine* physEngine);
    //!Returns the Drawable of the Player
    Drawable* returnPlayerDrawable();
    //!return the DynamicCam of the character
    DynamicCharacterWithCam* returnPlayerCam();
    //!return the players ModelTransformation
    ModelTransformation* returnModelTransformation();
private:
    //!PlayerModel currently only Fighter
    Drawable* v_PlayerModel;
    //!Camera for the Player
    DynamicCharacterWithCam* v_PlayerCharacter;
    //!Texture for the PlayerModel
    Texture* v_Texture;
    //!reference to a shader for texture
    Shader* s_TextureShader;
    //!Transformation for the playerModel
    ModelTransformation *t_PlayerTransformation;
    //!PhysicConstructionInfo for the player physic Object
    PhysicObjectConstructionInfo* v_PlayerPhyObjConstInfo;
    //!Reference to the Physic Engine
    PhysicEngine* v_PhysicEngine;
    //!
    DynamicCharacterWithCam* v_CharacterCam;
};

#endif // PLAYER_H
