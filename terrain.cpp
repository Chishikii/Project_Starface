#include "terrain.h"


Terrain::Terrain(Heightmap *heightmap){
    this->heightmap = heightmap;
    mesh = heightmap->mesh;
}

void Terrain::fillVertices(QVector<QVector4D> &vertices){
    vertices.clear();
    vertices = *mesh;
}

void Terrain::fillNormals(QVector<QVector3D> &normals, QVector<QVector4D> &vertices){
    normals.clear();

    for(int i = 0; i < mesh->length() - 3; i += 3){
        QVector<QVector3D> buffer;

        //save triangle with index i in a buffer and pass it to newells Algorithm
        for(int j = 0; j < 3; j++){
            buffer.append( mesh->at(i+j).toVector3D());
        }

        QVector3D normal = newellNormals(buffer);

        //append normal for all vertices of tringle with index i
        normals.append(normal);
        normals.append(normal);
        normals.append(normal);
    }
}

void Terrain::render(Drawable *d){
    glFunctions->glDrawArrays(GL_TRIANGLES,0,mesh->length());
}

//function to calculate normals with newells Algorithm
QVector3D Terrain::newellNormals(QVector<QVector3D> inputVertices)
{
    QVector3D out;
    unsigned int length = inputVertices.length();

    for (int i=0; i<inputVertices.length(); i++)
    {
        out[0] += ((inputVertices[i][1]-inputVertices[(i+1)%length][1]) * (inputVertices[i][2]+inputVertices[(i+1)%length][2]))/2;
        out[1] += ((inputVertices[i][2]-inputVertices[(i+1)%length][2]) * (inputVertices[i][0]+inputVertices[(i+1)%length][0]))/2;
        out[2] += ((inputVertices[i][0]-inputVertices[(i+1)%length][0]) * (inputVertices[i][1]+inputVertices[(i+1)%length][1]))/2;
    }

    return (out.normalized());
}
