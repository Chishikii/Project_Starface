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

   //create map
   for(int y = 1; y < sizeY + 1; y++){
       for(int x = 1; x < sizeX + 1; x++){
           QRgb value;
           value = qRgb(x, y, x+y);
           map->setPixel(x, y, value);
       }
   }
   return true;
}

bool Heightmap::saveMap(){
   return map->save(QDir::homePath() + QString("/Desktop/test2.png"));
}
