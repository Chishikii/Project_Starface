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

Node *initScene1();

void SceneManager::initScenes()
{
    Heightmap *map = new Heightmap(100, 100);
    bool test = map->createMap();
    map->saveMap();
    printf("%d", test);
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


    Drawable *model = new Drawable(new TriangleMesh(":/modelObjects/fighter.obj"));

    Texture* t;
    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));

    Transformation *pos = new Transformation();

    // Nodes anlegen
    Node *root = new Node(pos);
    //temp node
    Node *posNode = new Node();
    Node* modelNode = new Node(model);

    //Texturen laden
    t = model->getProperty<Texture>();
    t->loadPicture(":/modelTextures/fighter_texture.png");

    //Shader fuer Textur setzen
    model->setShader(s);

    //temp position
    pos->translate(0.0, -3.0, -15.0);
    pos->rotate(20,QVector3D(1,0,0));


    // Baum aufbauen
    root->addChild(posNode);
    posNode->addChild(modelNode);
    return(root);
}

