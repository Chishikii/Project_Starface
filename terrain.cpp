#include "terrain.h"


Terrain::Terrain(Heightmap *heightmap){
    this->heightmap = heightmap;
    mesh = heightmap->mesh;
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
    normals.clear();
    for(int i = 0; i < mesh->length();i++){
        normals.append(QVector3D(0,1,0));
    }
/*
    for(int y = 0; y < heightmap->mapSize;y++){
        for(int x = 0; x < heightmap->mapSize;y++){
            //todo normals

        }
    }
*/
}

void Terrain::render(Drawable *d){
    glFunctions->glDrawArrays(GL_TRIANGLES,0,mesh->length());
}
