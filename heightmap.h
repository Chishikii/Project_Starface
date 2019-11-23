#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QImage>
#include <QFile>
#include <QDir>
#include <QVector4D>
#include "simplexnoise.h"

class Heightmap {
public:

    Heightmap();
    Heightmap(int size, int heightFactor, int strechFactor);
    //vector with all the vertices
    QVector<QVector4D> *mesh;
    int mapSize;

protected:
    //creates mesh with attributes and noise
    void createMeshArray();
    //returns value between [0] and [1]
    float evaluateNoise(int x, int y);
    //image for noise testing
    bool createMap();
    bool saveMap();
private:
    //noise
    SimplexNoise *noise;
    //base values: f= 0.01, a = 1, lac = 2, pers = 0.5
    float frequency = 0.02;     //Frequency ("width") of the first octave of noise (default to 1.0)
    float amplitude = 1.5;      //Amplitude ("height") of the first octave of noise (default to 1.0)
    float lacunarity = 2;     //Lacunarity specifies the frequency multiplier between successive octaves (default to 2.0).
    float persistence = 0.5;    //Persistence is the loss of amplitude between successive octaves (usually 1/lacunarity)
    //attributes for the mesh
    int height = 100;
    int factor = 10;
    //testing image
    QImage *map;
};

#endif // HEIGHTMAP_H
