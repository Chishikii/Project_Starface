#include "terrain.h"


Terrain::Terrain(Heightmap heightmap){
    this->heightmap = new QImage();
    mesh = heightmap.mesh;
    meshSize = heightmap.mapSize;
}

void Terrain::fillVertices(QVector<QVector4D> &vertices){
    vertices.clear();
    vertices = *mesh;
}

void Terrain::fillColors(QVector<QVector4D> &colors){
    colors.clear();
    for(int i = 0; i < mesh->length();i++){
        int gray = 255*mesh->at(i).y();
        colors.append(QVector4D(gray,gray,gray,1));
    }
}

void Terrain::fillNormals(QVector<QVector3D> &normals, QVector<QVector4D> &vertices){
    for(int i = 0; i < mesh->length();i++){
        normals.append(QVector3D(0,1,0));
    }
}

void Terrain::render(Drawable *d){
    glFunctions->glDrawArrays(GL_TRIANGLES,0,6*(meshSize)*(meshSize));
}
