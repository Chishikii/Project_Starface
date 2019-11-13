#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <QImage>
#include <QFile>

class Heightmap {
public:
    int sizeX;
    int sizeY;
    QImage *map;

    Heightmap();
    Heightmap(int sizeX, int sizeY);
    bool createMap();
    bool saveMap();
};

#endif // HEIGHTMAP_H
