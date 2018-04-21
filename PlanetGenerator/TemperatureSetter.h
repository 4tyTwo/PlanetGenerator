#pragma once
#include "Map.h"
//Абстрактный класс, который при помощи статического метода будет задавать температуру клеток переданной карты
//Температура - функция от высоты, влажности и координаты
class TemperatureSetter
{
public:
  static void setTemperature(Map* map, int baseTemp);
  virtual ~TemperatureSetter() = 0;
};

