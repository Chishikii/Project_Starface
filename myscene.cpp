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
unsigned int myScene, myScene2;
SoundSource *gSoundSource1, *gSoundSource2, *gSoundSource3, *gAmbientSoundSource;
Node* gAudioListenerNode;

class SceneSwitcher: public Listener
{
    void keyboard(int key, int modifier)
    {
        if (key == '1')
        {
            sortedRenderer->setScene(myScene);
            gSoundSource1->play();
        }
        else if(key =='2')
        {
            sortedRenderer->setScene(myScene2);
            gSoundSource2->play();
        }
        else if (key == 'l' || key == 'L')
        {
            gSoundSource3->play();
        }
    }
};

void SceneManager::initScenes()
{
    SceneSwitcher* lSwitch = new SceneSwitcher();
    Camera* cam = new Camera();
    CameraController* camController = new MouseKeyboardCameraController(cam);
    Q_UNUSED(camController)
    RenderingContext* myContext = new RenderingContext(cam);
    unsigned int myContextNr = SceneManager::instance()->addContext(myContext);
    myScene = SceneManager::instance()->addScene(initScene1());
    myScene2 = SceneManager::instance()->addScene(initScene2());
    sortedRenderer = new ScreenRenderer(myContextNr, myScene);
    Q_UNUSED(lSwitch)

    //Vorsicht: Die Szene muss initialisiert sein, bevor das Fenster verändert wird (Fullscreen)
    SceneManager::instance()->setActiveScene(myScene);
    SceneManager::instance()->setActiveContext(myContextNr);
    SceneManager::instance()->setFullScreen();
}

Node *initScene1()
{
    //Objekte anlegen
    QString path(SRCDIR); //aus .pro-File!

    //AudioListener anlegen
    AudioListener* lAudioListener= new AudioListener();
    gAudioListenerNode = new Node(lAudioListener);

    //Sounds initialisieren, Fallback auf Stereo, falls OpenAL nicht verfügbar
    AudioEngine::instance().init(AudioEngineType::OpenAL3D);
    //Oder direkt Qt Sound verwenden
    //    AudioEngine::instance().init(AudioEngineType::QtStereo);

    //Wichtig: OpenAL kann Sounds nur in WAV 16 Bit
    //Wenn 3D-Sound erzeugt werden soll, müssen diese außerdem MONO sein!
    gSoundSource1 = new SoundSource(new SoundFile(path+QString("/sounds/Hammering.wav")));
    gSoundSource2 = new SoundSource(new SoundFile(path+QString("/sounds/CityAmbiance.wav")));
    gSoundSource3 = new SoundSource(new SoundFile(path+QString("/sounds/LaserCannon.wav")));
    Node *lSource1Node = new Node(gSoundSource1);
    Node *lSource2Node = new Node(gSoundSource2);
    Node *lSource3Node = new Node(gSoundSource3);

    //NatureAmbience ist Stereo und ändert daher als ambienter Sound seine "Position" nicht
    gAmbientSoundSource = new SoundSource(new SoundFile(path+QString("/sounds/NatureAmbiance.wav")));
    gAmbientSoundSource->setLooping(true);
    gAmbientSoundSource->play();

    Node *root = new Node();
    Drawable *model2 = new Drawable(new TriangleMesh(path+QString("/modelstextures/skyCaveShip.obj")));

    //Geometrien können mehrfach verwendet werden -> gleiche Geometrie, anderes Erscheinungsbild
    Geometry* g = new TriangleMesh(path + QString("/modelstextures/ogrehead.obj"));
    Drawable* model1 = new Drawable(g);
    Drawable* model = new Drawable(g);
    Texture* t;
    Shader* s = ShaderManager::getShader(path + QString("/shader/texture.vert"), path + QString("/shader/texture.frag"));
    Transformation *pos = new Transformation(), *pos2 = new Transformation();

    // Nodes anlegen
    Node* model1Node = new Node(model1);
    Node* posNode = new Node(pos);
    Node* modelNode = new Node(model);
    Node* pos2Node = new Node(pos2);
    Node* model2Node = new Node(model2);

    model1->deactivateFill();
    //Texturen laden
    t = model->getProperty<Texture>();
    t->loadPicture(path + QString("/modelstextures/ogrehead_diffuse.png"));

    //Texturen laden
    t = model2->getProperty<Texture>();
    t->loadPicture(path + QString("/modelstextures/skyCaveShip_TEX.png"));

    //Shader fuer Textur setzen
    model->setShader(s);
    model2->setShader(s);

    pos->translate(2.0, 0.0, 0.0);
    pos2->translate(0.0, 3.0, 0.0);

    KeyboardTransformation *lKB = new KeyboardTransformation();
    Node *lKBNode = new Node(lKB);
    lKB->setTransKeys('l','L',
                     KeyboardTransformation::NoKey, KeyboardTransformation::NoKey,
                     KeyboardTransformation::NoKey, KeyboardTransformation::NoKey);

    // Baum aufbauen
    root->addChild(gAudioListenerNode);
    root->addChild(model1Node);
    posNode->addChild(lSource1Node);
    root->addChild(posNode);
    posNode->addChild(modelNode);
    root->addChild(lKBNode);
    posNode->addChild(lSource2Node);
    lKBNode->addChild(pos2Node);
    pos2Node->addChild(model2Node);
    pos2Node->addChild(lSource3Node);
    return(root);
}

Node *initScene2()
{
//    Objekte anlegen
    Planet* sonne = new Planet(1.0);
    KeyboardTransformation* sonnensystem = new KeyboardTransformation();
    KeyboardTransformation *erdrotation = new KeyboardTransformation();
    KeyboardTransformation *mondrotation = new KeyboardTransformation();
    Transformation *erdUmlaufbahn = new Transformation();
    Transformation *mondOrbit = new Transformation();
    Planet *meineErde = new Planet(0.2F);
    Planet *meinMond = new Planet(0.05F);
    Color *c;
    float mondspeed = 7.0, umlaufspeed=mondspeed/12.0, erdspeed=mondspeed*28.0;

    // Nodes anlegen
    Node* sonneNode = new Node(sonne);
    Node* sonnensystemNode = new Node(sonnensystem);
    Node* erdrotationNode = new Node(erdrotation);
    Node* mondrotationNode = new Node(mondrotation);
    Node* erdUmlaufbahnNode = new Node(erdUmlaufbahn);
    Node* mondOrbitNode = new Node(mondOrbit);
    Node* meineErdeNode = new Node(meineErde);
    Node* meinMondNode = new Node(meinMond);

    //Farben
    c = sonne->getProperty<Color>();
    c->setValue(1.0,1.0,0.0,1.0);
    c = meineErde->getProperty<Color>();
    c->setValue(0.0,0.0,1.0,1.0);
    c = meinMond->getProperty<Color>();
    c->setValue(0.7F,0.7F,0.7F,1.0F);

    //Damit man die Drehungen sieht, Gitternetz aktivieren
    sonne->deactivateFill();
    meineErde->deactivateFill();
    meinMond->deactivateFill();

    //Keys belegen
    sonnensystem->setRotKeys(KeyboardTransformation::NoKey,
                             KeyboardTransformation::NoKey,
                             'r', 'R',
                             KeyboardTransformation::NoKey,
                             KeyboardTransformation::NoKey);
    sonnensystem->setRotspeed(umlaufspeed);
    erdrotation->setRotKeys('r', 'R',
                            KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey
                            );
    erdrotation->setRotspeed(erdspeed);
    mondrotation->setRotKeys(KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey,
                            KeyboardTransformation::NoKey,
                             'r', 'R'
                             );
    mondrotation->setRotspeed(mondspeed);

    //Vorsicht beim ändern von Rot. und Trans. derselben Transformation:
    //Die Reihenfolge ist wichtig!
    sonnensystem->rotate(45.0, 1.0, 0.0, 0.0); // Neigen, damit man die Umlaufbahn besser sieht
    erdUmlaufbahn->translate(3.0, 0.0, 0.0);   // Erdumlaufbahn
    mondOrbit->translate(0.5, 0.0, 0.0);

    // Szenengraph aufbauen
    sonnensystemNode->addChild(gAudioListenerNode);
    sonnensystemNode->addChild(sonneNode);
    sonneNode->addChild(erdUmlaufbahnNode);
    erdUmlaufbahnNode->addChild(erdrotationNode);
    erdUmlaufbahnNode->addChild(mondrotationNode);
    mondrotationNode->addChild(mondOrbitNode);
    mondOrbitNode->addChild(meinMondNode);
    erdrotationNode->addChild(meineErdeNode);
    erdrotationNode->addChild(new Node(gSoundSource1));
    return (sonnensystemNode);
}

