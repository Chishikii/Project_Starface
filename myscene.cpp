#include "scenemanager.h"
#include "screenrenderer.h"
#include "mousekeyboardcameracontroller.h"
#include "trianglemesh.h"
#include "texture.h"
#include "shader.h"
#include "listener.h"
#include "transformation.h"
#include "keyboardtransformation.h"
#include "planet.h"
#include "color.h"
#include "audioengine.h"
#include "soundsource.h"
#include "shadermanager.h"
#include "efx-presets.h"

Node *initScene1();
Node *initScene2();

ScreenRenderer* sortedRenderer;
ScreenRenderer* preOrderRenderer;
unsigned int myScene;

void SceneManager::initScenes()
{
    Camera* cam = new Camera();
    CameraController* camController = new MouseKeyboardCameraController(cam);
    Q_UNUSED(camController)
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    myScene = SceneManager::instance()->addScene(initScene1());
    sortedRenderer = new ScreenRenderer(myContextNr, myScene);

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    //SceneManager::instance()->setFullScreen();
}

Node *initScene1()
{
    //Projectpath
    QString path(SRCDIR);

    Drawable *model = new Drawable(new TriangleMesh(path+QString("/modelstextures/Fighter.obj")));

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
    t->loadPicture(path + QString("/modelstextures/Fighter_TEX.png"));

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
