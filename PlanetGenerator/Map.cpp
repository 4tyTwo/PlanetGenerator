#include "Map.h"



Map::Map(){
}

Map::Map(int x_size, int y_size) {
  x_size_ = x_size;
  y_size_ = y_size; //Количество строк
  data = new Tile**[x_size_];
  for (int i = 0; i<x_size_; ++i){
    data[i] = new Tile*[y_size_];
    for (int j=0; j<y_size_;++j)
      data[i][j] = new Tile();
  }
}

Tile* Map::get(int x, int y) {
  if (x>=0 && x < x_size_ && y>=0 && y < y_size_)
    return data[x][y];
}

float Map::avgHeight() {
  float summ = 0.0;
  for (int i = 0;i < x_size_; i++)
    for (int j = 0; j < y_size_; j++)
      summ = summ + data[i][j]->Height();
  return summ/(x_size_ * y_size_);
}

Map::~Map(){
}
