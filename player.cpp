#include "player.h"

Player::Player()
{
    v_PlayerModel = Q_NULLPTR;
    v_PlayerCharacter = Q_NULLPTR;
    v_Texture = Q_NULLPTR;
    s_TextureShader = Q_NULLPTR;
    t_PlayerTransformation = Q_NULLPTR;
    v_PlayerPhyObjConstInfo = Q_NULLPTR;
    v_PhysicEngine = Q_NULLPTR;
}

Player::Player(QString playerMeshObjPath, QString playerTexturePath, Shader* textureShader, PhysicEngine* physEngine){
    //create Player Object and set Texture
    v_PlayerModel = new Drawable(new TriangleMesh(playerMeshObjPath));
    v_Texture = v_PlayerModel->getProperty<Texture>();
    v_Texture->loadPicture(playerTexturePath);
    v_PlayerModel->setShader(textureShader);

    t_PlayerTransformation = v_PlayerModel->getProperty<ModelTransformation>();

    //camera
    v_CharacterCam = physEngine->createNewDynamicCharacterWithCam(v_PlayerModel);
    v_CharacterCam->setCam(dynamic_cast<PhysicAccessableCamera*>(SceneManager::instance()->getActiveContext()->getCamera()));

    v_CharacterCam->setRelativeCamPosition(0.f,15.f,90.f);
    //v_CharacterCam->setUpDownView(-10.f);
    v_CharacterCam->setAccelarationFactor(2.f);
    v_CharacterCam->setBrakeFactor(2.f);
    v_CharacterCam->setMaxForwardNormalSpeed(200.f);

    //construction info
    v_PlayerPhyObjConstInfo = new PhysicObjectConstructionInfo();
    v_PlayerPhyObjConstInfo->setMass(10.f);
    v_PlayerPhyObjConstInfo->setCcdActivation(true);
    v_PlayerPhyObjConstInfo->setCollisionHull(CollisionHull::BoxAABB);

    v_PlayerModel->getPhysicObject()->setConstructionInfo(v_PlayerPhyObjConstInfo);
    v_PlayerModel->getPhysicObject()->registerPhysicObject();
    v_PlayerModel->getPhysicObject()->setGravity(QVector3D(0.f,0.f,0.f));
    v_PlayerModel->getPhysicObject()->setPhysicState(PhysicState::Dynamic);
    v_PlayerModel->getPhysicObject()->setPhysicType(PhysicType::Player);
}

Drawable* Player::returnPlayerDrawable(){
    return v_PlayerModel;
}

DynamicCharacterWithCam* Player::returnPlayerCam(){
    return v_CharacterCam;
}

ModelTransformation* Player::returnModelTransformation(){
    return t_PlayerTransformation;
}



