#include "heightmap.h"

Heightmap::Heightmap(){
    map = nullptr;
    mesh = nullptr;
    mapSize = 0;
    createMeshArray();
}
Heightmap::Heightmap(int size, int heightFactor, int strechFactor){
    Heightmap();
    noise = new SimplexNoise(frequency,amplitude,lacunarity,persistence);

    map = new QImage(size, size, QImage::Format_RGB32);
    mesh = new QVector<QVector4D>(size * size * 6);

    mapSize = size;

    //create and save map for testing
    createMap();
    saveMap();
    createMeshArray();
    //factor fo the mesh
    height = heightFactor;
    factor = strechFactor;
}
float Heightmap::evaluateNoise(int x, int y){

    float noiseValue = 0;

    //evaluate Noise at position x,y and determine gray value
    //full integer position gives 0 so take percantage of progress
    noiseValue = noise->fractal(5,x,y);
    //Value returned is between -1 and 1
    noiseValue = (noiseValue + 1)*0.5f;

    return noiseValue;
}
//function to create a triangle array for the mesh
void Heightmap::createMeshArray(){
    //vertex location on the map
    if(mapSize == 0) return;
    mesh->clear();
    int x, y;

    for(y = 0; y < mapSize*factor - 1; y+=factor){
        for(x = 0; x < mapSize*factor - 1; x+=factor){

            //left triangle
            mesh->append(QVector4D(x, height*evaluateNoise(x/factor,y/factor),y,1));
            mesh->append(QVector4D(x, height*evaluateNoise(x/factor,y/factor + 1),y + factor, 1));
            mesh->append(QVector4D(x + factor, height*evaluateNoise(x/factor + 1, y/factor), y, 1));

            //right triangle
            mesh->append(QVector4D(x + factor,height*evaluateNoise(x/factor + 1, y/factor),y,1));
            mesh->append(QVector4D(x, height*evaluateNoise(x/factor,y/factor + 1),y + factor, 1));
            mesh->append(QVector4D(x + factor, height*evaluateNoise(x/factor + 1, y/factor + 1), y + factor, 1));
        }
    }
}

//functions to create and save a testmap for the noise
bool Heightmap::createMap(){
   if (map == nullptr) return false;

   float gray = 0;


   //create map by iterating through each pixel
   for(int y = 0; y < map->height(); y++){
       for(int x = 0; x < map->width(); x++){


           gray = qGray((int)(255.0 * evaluateNoise(x,y)),(int)(255.0 * evaluateNoise(x,y)),(int)(255.0 * evaluateNoise(x,y)));

           //setting pixels to grayvalue
           map->setPixelColor(QPoint(x,y),QColor(gray,gray,gray).rgba());
       }
   }
   return true;
}
bool Heightmap::saveMap(){
   //save heightmap as png on Desktop
   return map->save(QDir::homePath() + QString("/Desktop/heightmap.bmp"));
}
