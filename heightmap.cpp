#include "heightmap.h"

Heightmap::Heightmap(){
    this->sizeY = 0;
    this->sizeX = 0;
    map = nullptr;
}
Heightmap::Heightmap(int sizeX, int sizeY){
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    map = new QImage(sizeX, sizeY, QImage::Format_RGB32);
}

bool Heightmap::createMap(){
   if (map == nullptr) return false;

   //createNoise
   SimplexNoise noise(0.01,1.0,2.0,0.5);
   float noiseValue = 0, gray = 0;

   //create map
   for(int y = 0; y < sizeY; y++){
       for(int x = 0; x < sizeX; x++){

           //evaluate Noise at position x,y and determine gray value
           //full integer position gives 0 so take percantage of the way also return between -1 and 1
           noiseValue = noise.fractal(5,x,y);
           noiseValue = (noiseValue + 1)*0.5f;

           gray = qGray((int)(255.0 * noiseValue),(int)(255.0 * noiseValue),(int)(255.0 * noiseValue));

           //setting pixels to grayvalue
           map->setPixelColor(QPoint(x,y),QColor(gray,gray,gray).rgba());
       }
   }
   return true;
}

bool Heightmap::saveMap(){
   return map->save(QDir::homePath() + QString("/Desktop/heightmap.png"));
}
