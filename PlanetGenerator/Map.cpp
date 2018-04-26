#include "Map.h"



Map::Map(){
}

void Map::setSeaLevel(float sea){
  SeaLevel_ = (abs(sea) > 1.0f) ? 1.0f : abs(sea);
}

Map::Map(int Height, int Width){
  Height_ = Height;
  Width_ = Width; //Количество строк
  data = new Tile**[Height_];
  for (int i = 0; i<Height_; ++i){
    data[i] = new Tile*[Width_];
    for (int j=0; j<Width_;++j)
      data[i][j] = new Tile();
  }
}

Tile* Map::get(int x, int y){
  if (x>=0 && x < Height_ && y>=0 && y < Width_)
    return data[x][y];
  return nullptr;
}

float Map::avgHeight(){
  float summ = 0.0;
  for (int i = 0;i < Height_; i++)
    for (int j = 0; j < Width_; j++)
      summ = summ + data[i][j]->Height();
  return summ/(Height_ * Width_);
}

float Map::maxHeight() {
  float max = 0.0f;
  for (int i = 0; i < Height_; i++)
    for (int j = 0; j < Width_; j++)
      if (data[i][j]->Height() > max)
        max = data[i][j]->Height();
  return max;
}

float Map::maxHumidity() {
  float max = 0.0f;
  for (int i = 0; i < Height_; i++)
    for (int j = 0; j < Width_; j++)
      if (data[i][j]->Humidity() > max)
        max = data[i][j]->Humidity();
  return max;
}

int Map::maxTemperature() {
  int max = 0;
  for (int i = 0; i < Height_; i++)
    for (int j = 0; j < Width_; j++)
      if (data[i][j]->Temperature() > max)
        max = data[i][j]->Temperature();
  return max;
}

Map::~Map(){
}
