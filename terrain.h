#ifndef TERRAIN_H
#define TERRAIN_H

#include "geometry.h"
#include "heightmap.h"

class Terrain : public Geometry
{
public:
    Terrain(Heightmap *heightmap);
protected:
    virtual void fillVertices(QVector<QVector4D> &vertices) override;
    virtual void fillNormals(QVector<QVector3D> &normals, QVector<QVector4D> &vertices) override;
    virtual void render(Drawable *d) override;
    QVector3D newellNormals(QVector<QVector3D> inputVertices);
private:
    Heightmap *heightmap;
    //array with vertices generated by heightmap
    QVector<QVector4D> *mesh;
    int meshSize;
};

#endif // TERRAIN_H
