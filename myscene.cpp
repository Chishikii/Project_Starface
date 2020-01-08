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


#include "sunlight.h"
#include <QDebug>

#include "player.h"

Node *initScene1();
Node *initScene2();

ScreenRenderer* sortedRenderer;
ScreenRenderer* preOrderRenderer;
unsigned int myScene1, myScene2;

class SceneSwitcher: public Listener
{
    void keyboard(int key, int modifier)
    {
        if (key == 'g')
        {
            sortedRenderer->setScene(myScene1);
        }
        else if(key =='h')
        {
            sortedRenderer->setScene(myScene2);

        }
    }
};

void SceneManager::initScenes()
{
    /*SceneSwitcher* lSwitch = new SceneSwitcher();
    PhysicAccessableCamera* cam = new PhysicAccessableCamera();
    cam->setFarPlane(5000.f);
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    unsigned int myScene = SceneManager::instance()->addScene(initScene1());*/

    SceneSwitcher* lSwitch = new SceneSwitcher();
    PhysicAccessableCamera* cam = new PhysicAccessableCamera();
    cam->setXAngleTripod(30.f);
    cam->setFarPlane(5000.f);
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    myScene1 = SceneManager::instance()->addScene(initScene1());
    myScene2 = SceneManager::instance()->addScene(initScene2());
    sortedRenderer = new ScreenRenderer(myContextNr, myScene1);
    Q_UNUSED(lSwitch);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene1);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();


    /*Q_UNUSED(myRenderer)
    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    //SceneManager::instance()->setFullScreen();*/
}

Node *initScene1()
{
    QString path(SRCDIR);
    //    Objekte anlegen

    /*Plane *StartMenu = new Plane(100,100);
    Texture *t = StartMenu->getProperty<Texture>();
    t->loadPicture(":/modelTextures/fighter_texture.png");*/

    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    //Drawable *StartMenu = new Drawable(new TriangleMesh(":/modelObjects/fighterRot.obj"));
    Drawable *StartMenu = new Drawable(new TriangleMesh(":/modelObjects/MainMenu2.obj"));
    StartMenu->setStaticGeometry(false);
    //Texturen laden
    Texture *t = StartMenu->getProperty<Texture>();
    //t->loadPicture(":/modelTextures/fighter_texture.png");
    t->loadPicture(":/modelTextures/StartMenu.png");
    StartMenu->setShader(s);

    Transformation *MenuPos= new Transformation();

    MenuPos->rotate(90,QVector3D(1,0,0));
    MenuPos->translate(0.0,0.0,-16.0);
    MenuPos->scale(3.9,3.9,3.9);



    //watersurface->translate(0.0,0.0,-50);
    Node *root = new Node();
    Node *StartMenuNode = new Node(StartMenu);
    Node *MenuPosNode = new Node(MenuPos);

    root->addChild(MenuPosNode);
    MenuPosNode->addChild(StartMenuNode);

    return(root);
}


Node *initScene2()
{
     //Projectpath
    QString path(SRCDIR);

    int terrainSize = 200;

    //Terrain
    Heightmap *map = new Heightmap(terrainSize,200,50);
    Terrain *terrain = new Terrain(map);


    //Water
    /*Plane *water = new Plane(100,100);

    Transformation *watersurface= new Transformation();
    Shader* w = ShaderManager::getShader(path + QString("/shader/water.vert"), path + QString("/shader/water.frag"));

    watersurface->rotate(0.0,90.0,0.0,0.0);
    //watersurface->translate(0.0,0.0,-50);
    water->setShader(w);

    Node *waterNode = new Node(water);
    Node *watersurfaceNode = new Node(watersurface);*/


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

    //RingCourse hinzufügen
    Drawable *RingCourse = new Drawable(new TriangleMesh(":/modelObjects/RingCourse.obj"));

    Texture *t = RingCourse->getProperty<Texture>();
    t->loadPicture(":/modelTextures/RingCourse.png");
    RingCourse->setShader(s);

    Transformation *RingCoursePos= new Transformation();

    RingCoursePos->scale(5.0,5.0,5.0);


    Node *RingCourseNode = new Node(RingCourse);
    Node *RingCoursePosNode = new Node(RingCoursePos);



    //Shader fuer Textur setzen
    //v_fighterModel->setShader(s);
    terrainModel->setShader(b);
    //terrainModel->setShader(s);

    //posTerrain->translate(-terrainSize*10/2,-100,-terrainSize*10);
    //posTerrain->rotate(-20,QVector3D(1,0,0));

    // Baum aufbauen

    root->addChild(transformationTerrainNode);
    root->addChild(RingCoursePosNode);
    RingCoursePosNode->addChild(RingCourseNode);
    /*root->addChild(watersurfaceNode);
    watersurfaceNode->addChild(waterNode);*/


    return(root);
}

