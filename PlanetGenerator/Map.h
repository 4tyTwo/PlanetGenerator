#pragma once
#include "Tile.h"
//Сюда надо записать всякую инфу типа максимальной высоты, уровня моря и т.д. так намного лучше.
class Map
{
public:
  //Конструкторы
  Map(int Height,int Width); //Со

  //Set методы
  void setSeaLevel(float sea);
  //Get методы
  inline int Height() { return Height_; }
  inline int Width() { return Width_; }
  inline float SeaLevel() { return SeaLevel_; }
  Tile* get(int x,int y); //Получить по адресу
  Tile** operator[](int x) { return data[x]; } //Получить ряд по индексу ряда

  //Служебные методы
  float avgHeight(); //Средняя высота карты
  float maxHeight(); //Самая высокая точка карты
  float maxHumidity(); //Максимальная влажность суши
  float minHumidity(); //Минимальная влажность суши
  int maxTemperature(); 
  
  //Деструктор
  ~Map();
private:
  Map() {}
  int Height_,Width_;
  float SeaLevel_;
  Tile ***data;
};

