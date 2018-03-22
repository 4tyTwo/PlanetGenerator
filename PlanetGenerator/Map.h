#pragma once
#include "Tile.h"
class Map
{
public:
  //Конструктор
  Map(int x_size,int y_size);
  Map();

  //Get функции
  inline int x_size() { return x_size_; }
  inline int y_size() { return y_size_; }
  Tile* get(int x,int y); //Получить по адресу
  Tile** operator[](int x) { return data[x]; } //Получить ряд по индексу ряда

  //Служебные функции
  float avgHeight(); //Средняя высота карты
  
  ~Map();
private:
  int x_size_,y_size_;
  Tile ***data;
};

