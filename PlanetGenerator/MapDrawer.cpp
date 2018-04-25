#include "MapDrawer.h"



MapDrawer::MapDrawer()
{
}

void MapDrawer::drawPhysicalMap(const std::string & filename){
  std::string water = "water", mountain = "mountain";
  int height = getMap().Height(), width = getMap().Width();
  sf::Uint8 red,green,blue, alpha = 255;
  sf::Uint8 *pixels = new sf::Uint8[height * width * 4]; //Не забудь почистить память потом
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      if (!getMap()[j][i]->Type().compare(water)){
          red = 0, green = 0, blue = 255;
      }
      else {
        if (!getMap()[j][i]->Type().compare(mountain)) {
          red = 142, green = 71, blue = 53;
        }
        else {
          red = 0, green = 255, blue = 0;
        }
      }
    pixels[(i + j * width) * 4] = red;
    pixels[(i + j * width) * 4 + 1] = green;
    pixels[(i + j * width) * 4 + 2] = blue;
    pixels[(i + j * width) * 4 + 3] = alpha;
    }
  sf::Image img;
  img.create(width, height, pixels);
  img.saveToFile(filename);
  delete[] pixels;
}

void MapDrawer::generate() {
  //Все карты разом
}
MapDrawer::~MapDrawer()
{
}
