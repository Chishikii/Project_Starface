#include "opengl.h"
#include "scene.h"
#include "scenemanager.h"
#include "screenrenderer.h"
#include "mainwindow.h"

#include "mousekeyboardcameracontroller.h"
#include "charactercontroller.h"
#include "trianglemesh.h"
#include "texture.h"
#include "shader.h"
#include "transformation.h"
#include "keyboardtransformation.h"
#include "color.h"
#include "shadermanager.h"
#include "heightmap.h"
#include "terrain.h"
#include "simpleplane.h"
#include "physicaccessablecamera.h"
#include "modeltransformation.h"
#include "simplesphere.h"
#include <QDebug>

#include "player.h"

Node *initScene1();

void SceneManager::initScenes()
{

    PhysicAccessableCamera* cam = new PhysicAccessableCamera();
    cam->setXAngleTripod(30.f);
    cam->setFarPlane(5000.f);
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(myRenderer)
    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();
}

Node *initScene1()
{
    //Projectpath
    QString path(SRCDIR);

    int terrainSize = 200;

    //Terrain
    Heightmap *map = new Heightmap(terrainSize,200,50);
    Terrain *terrain = new Terrain(map);

    //shader
    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    Shader* b = ShaderManager::getShader(path + QString("/shader/heightmapSimple.vert"),path + QString("/shader/heightmapSimple.frag"));

    // Nodes anlegen
    Node *root = new Node();

    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    //Create TerrainNode and Physics
    Drawable *terrainModel = new Drawable(terrain);
    terrainModel->setStaticGeometry(false);
    Transformation* v_TransformationTerrain = new Transformation();
    Node* transformationTerrainNode = new Node(v_TransformationTerrain);
    v_TransformationTerrain->translate(-terrainSize*50/2,-200,-terrainSize*50/2);
    PhysicObject* v_terrainPhysObject = v_PhysicEngine->createNewPhysicObject(terrainModel);

    v_terrainPhysObject->setPhysicState(PhysicState::Static);
    v_terrainPhysObject->setPhysicType(PhysicType::Object);

    PhysicObjectConstructionInfo* v_terrainObjectConstructionInfo = new PhysicObjectConstructionInfo();
    v_terrainObjectConstructionInfo->setCollisionHull(CollisionHull::BVHTriangleMesh);
    v_terrainPhysObject->setConstructionInfo(v_terrainObjectConstructionInfo);
    v_terrainPhysObject->registerPhysicObject();
    transformationTerrainNode->addChild(new Node(terrainModel));
    terrainModel->setShader(b);

    //create and add player
    Player* playerObj = new Player(QString(":/modelObjects/fighterRot.obj"),QString(":/modelTextures/fighter_texture.png"),s,v_PhysicEngine);
    root->addChild(new Node(playerObj->returnPlayerDrawable()));
    new CharacterController(playerObj->returnPlayerCam(),playerObj->returnModelTransformation());

    // Baum aufbauen
    root->addChild(transformationTerrainNode);


    return(root);
}

