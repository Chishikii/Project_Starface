#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
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

#include <QDebug>

Node *initScene1();

void SceneManager::initScenes()
{

    Camera* cam = new Camera();
    CameraController* camController = new MouseKeyboardCameraController(cam);
    Q_UNUSED(camController)
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());
    ScreenRenderer *myRenderer = new ScreenRenderer(myContextNr, myScene);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();
}

Node *initScene1()
{
    //Projectpath
    QString path(SRCDIR);

    int terrainSize = 20;

    //Terrain
    Heightmap *map = new Heightmap(terrainSize,10,1);
    Terrain *terrain = new Terrain(map);

    //shader
    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    Shader* b = ShaderManager::getShader(path + QString("/shader/heightmapSimple.vert"),path + QString("/shader/heightmapSimple.frag"));

    //Temp transform for position
    Transformation *pos = new Transformation();
    Transformation *posTerrain = new Transformation();
    Transformation *scale = new Transformation();

    // Nodes anlegen
    Node *root = new Node();
    //temp pos node
    Node *posNode = new Node(pos);
    //temp scale node
    Node *scaleNode = new Node(scale);

    int v_Slot = PhysicEngineManager::createNewPhysicEngineSlot(PhysicEngineName::BulletPhysicsLibrary);
    PhysicEngine* v_PhysicEngine = PhysicEngineManager::getPhysicEngineBySlot(v_Slot);

    //Create TerrainNode and Physics
    Drawable *terrainModel = new Drawable(terrain);
    terrainModel->setStaticGeometry(true);
    Transformation* v_TransformationTerrain = new Transformation();
    Node* transformationTerrainNode = new Node(v_TransformationTerrain);
    v_TransformationTerrain->translate(-terrainSize*10/2,-100,-terrainSize*10);
    PhysicObject* v_terrainPhysObject = v_PhysicEngine->createNewPhysicObject(terrainModel);
    PhysicObjectConstructionInfo* v_terrainObjectConstructionInfo = new PhysicObjectConstructionInfo();
    v_terrainObjectConstructionInfo->setCollisionHull(CollisionHull::BoxCovarianceFromPoints);
    v_terrainPhysObject->setConstructionInfo(v_terrainObjectConstructionInfo);
    v_terrainPhysObject->registerPhysicObject();
    transformationTerrainNode->addChild(new Node(terrainModel));

    //Create FighterNode and Physics
    Drawable *fighterModel = new Drawable(new TriangleMesh(":/modelObjects/fighterRot.obj"));
    //Texturen laden
    Texture *t;
    t = fighterModel->getProperty<Texture>();
    t->loadPicture(":/modelTextures/fighter_texture.png");
    //fighterModel->setStaticGeometry(true);
    Transformation* v_TransformationFighter = new Transformation();
    Node* transformationFighterNode = new Node(v_TransformationFighter);
    v_TransformationFighter->scale(QVector3D(0.1,0.1,0.1));
    PhysicObject* v_fighterPhysObject = v_PhysicEngine->createNewPhysicObject(fighterModel);
    PhysicObjectConstructionInfo* v_fighterObjectConstructionInfo = new PhysicObjectConstructionInfo();
    v_fighterObjectConstructionInfo->setMass(10.f);
    v_fighterObjectConstructionInfo->setCollisionHull(CollisionHull::BoxCovarianceFromPoints);
    v_fighterPhysObject->setConstructionInfo(v_fighterObjectConstructionInfo);
    v_fighterPhysObject->registerPhysicObject();
    transformationFighterNode->addChild(new Node(fighterModel));


    //Shader fuer Textur setzen
    fighterModel->setShader(s);
    terrainModel->setShader(b);
    //terrainModel->setShader(s);

    //temp position
    pos->translate(0.0, -3.0, -15.0);
    //pos->rotate(180,QVector3D(0,1,0));
    pos->rotate(-20,QVector3D(1,0,0));

    //temp scale
    scale->scale(QVector3D(0.1,0.1,0.1));

    posTerrain->translate(-terrainSize*10/2,-100,-terrainSize*10);
    //posTerrain->rotate(-20,QVector3D(1,0,0));

    // Baum aufbauen
    root->addChild(posNode);
    root->addChild(transformationFighterNode);
    root->addChild(transformationTerrainNode);


    return(root);
}

