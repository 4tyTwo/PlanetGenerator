#include "MapDrawer.h"



MapDrawer::MapDrawer()
{
}

void MapDrawer::drawPhysicalMap(const std::string & filename){
  int height = getMap().Height(), width = getMap().Width();
  sf::Uint8 red,green,blue, alpha = 255;
  sf::Uint8 *pixels = new sf::Uint8[height * width * 4]; //Не забудь почистить память потом
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      if (getMap()[j][i]->Type() == 0 || getMap()[j][i]->Type() == 12){
          red = 0, green = 0, blue = 255;
      }
      else {
        if (getMap()[j][i]->Type() == 1) {
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

void MapDrawer::drawHumidMap(const std::string & filename) {
  int height = getMap().Height(), width = getMap().Width();
  sf::Uint8 red = 0, green = 0, blue, alpha = 255;
  sf::Uint8 *pixels = new sf::Uint8[height * width * 4]; //Не забудь почистить память потом
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      blue = getMap()[j][i]->Humidity() * 255;
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

void MapDrawer::drawTempMap(const std::string & filename){
  int height = getMap().Height(), width = getMap().Width();
  sf::Uint8 red = 0, green = 0, blue, alpha = 255;
  sf::Uint8 *pixels = new sf::Uint8[height * width * 4]; //Не забудь почистить память потом
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
        if (getMap()[j][i]->Type()!= 0 && getMap()[j][i]->Type() != 12){
          if (getMap()[j][i]->Temperature() > 21) {
            // 25+
            red = 255;
            green = 0 + (getMap()[j][i]->Temperature() - 21) * 83 / 20; //из 0 в 83
            blue = 0;
          }
          else {
            if (getMap()[j][i]->Temperature() > 16) {
              //20-25
              red = 255;
              green = 83 + (getMap()[j][i]->Temperature() - 16) * 172 / 5; //Из 83 в 255
              blue = 0;
            }
            else {
              if (getMap()[j][i]->Temperature() > 11) {
                //15-20
                red = 255 - (getMap()[j][i]->Temperature() - 11) * 35; // Из 255 в 80
                green = 255 - (getMap()[j][i]->Temperature() - 11) * 11; //Из 255 в 200
                blue = 0 + (getMap()[j][i]->Temperature() - 11) * 24; //Из 0 в 120
              }
              else {
                if (getMap()[j][i]->Temperature() > 7) {
                  //10-15
                  red = 80 + (getMap()[j][i]->Temperature() - 7); //Из 80 в 85
                  green = 200 - (getMap()[j][i]->Temperature() - 7) * 5; //Из 200 в 175
                  blue = 120 + (getMap()[j][i]->Temperature() - 7) * 27; //Из 120 в 255
                }
                else {
                  if (getMap()[j][i]->Temperature() > 0) {
                    //5-10
                    red = 85 + (getMap()[j][i]->Temperature() - 0) * 170 / 7;
                    green = 175 + (getMap()[j][i]->Temperature() - 0) * 80 / 7;
                    blue = 255;
                  }
                  else {
                    //0-
                    red = 255;
                    green = 255;
                    blue = 255;
                  }
                }
              }
            }
          }
        }
        else {
          red = 0;
          green = 0;
          blue = 0;
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

void MapDrawer::drawBiomeMap(const std::string & filename){
  int height = getMap().Height(), width = getMap().Width();
  float seaLevel = getMap().SeaLevel();
  sf::Uint8 red = 0, green = 0, blue, alpha = 255;
  sf::Uint8 *pixels = new sf::Uint8[height * width * 4]; //Не забудь почистить память потом
  for (int i = 0; i < width; i++)
    for (int j = 0; j < height; j++) {
      switch (getMap()[j][i]->Type()){
        case 0:{
          red = 0, green = 0, blue = 255 - (seaLevel - getMap()[j][i]->Height())*255;
          break;
        }
        case 1:{
          red = 142, green = 71, blue = 53;
          break;
        }
        case 2:{
          red = 18, green = 79, blue = 49;
          break;
        }
        case 3:{
          red = 0, green = 77, blue = 0;
          break;
        }
        case 4:{
          red = 0, green = 128, blue = 43;
          break;
        }
        case 5:{
          red = 25, green = 25, blue = 25;
          break;
        }
        case 6:{
          red = 230, green = 230, blue = 0;
          break;
        }
        case 7:{
          red = 51, green = 204, blue = 51;
          break;
        }
        case 8:{
          red = 255, green = 255, blue = 26;
          break;
        }
        case 9:{
          red = 230, green = 255, blue = 153;
          break;
        }
        case 10:{
          red = 153, green = 204, blue = 0;
          break;
        }
        case 11:{
          red = 0, green = 204, blue = 0;
          break;
        }
        case 12:{
          red = 0; green = 0; blue = 255;   
          break;
        }      
        case 13: {
          red = 245, green = 245, blue = 245;
          break;
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
