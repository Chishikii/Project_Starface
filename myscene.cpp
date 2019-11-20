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

    int terrainSize = 100;

    //Terrain
    Heightmap *map = new Heightmap(terrainSize,100,10);
    Terrain *terrain = new Terrain(*map);

    //FighterObj
    Drawable *model = new Drawable(new TriangleMesh(":/modelObjects/fighter.obj"));
    //TerrainObj
    Drawable *terrainModel = new Drawable(terrain);

    //shader
    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));

    //Temp transform for position
    Transformation *pos = new Transformation();
    Transformation *posTerrain = new Transformation();
    Transformation *scale = new Transformation();

    // Nodes anlegen
    Node *root = new Node();
    //temp pos node
    Node *posNode = new Node(pos);
    Node *posTerrainNode = new Node(posTerrain);
    //temp scale node
    Node *scaleNode = new Node(scale);
    //Model nodes
    Node* modelNode = new Node(model);
    Node* terrainNode = new Node(terrainModel);

    //Texturen laden
    Texture *t;
    t = model->getProperty<Texture>();
    t->loadPicture(":/modelTextures/fighter_texture.png");

    //Shader fuer Textur setzen
    model->setShader(s);
    //terrainModel->setShader(s);

    //temp position
    pos->translate(0.0, -3.0, -15.0);
    pos->rotate(180,QVector3D(0,1,0));
    pos->rotate(-20,QVector3D(1,0,0));

    //temp scale
    scale->scale(QVector3D(0.1,0.1,0.1));

    posTerrain->translate(-terrainSize*10/2,-100,-terrainSize*10);
    //posTerrain->rotate(-20,QVector3D(1,0,0));


    // Baum aufbauen
    root->addChild(posNode);
    root->addChild(posTerrainNode);
    posNode->addChild(scaleNode);
    scaleNode->addChild(modelNode);
    posTerrainNode->addChild(terrainNode);

    return(root);
}

