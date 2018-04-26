#pragma once
#include <algorithm>
#include <vector>
/* 
    ТИПЫ:
    0 - вода
    1 - горы
    2 - Арктическая пустыня
    3 - Тундра
    4 - Тайга
    5- Субарктика
    6 - Степь
    7 - лес
    8 - Пустыня
    9 - Саванна
    10 - Субтропический лес
    11 - Дождевой лес
    остальные - ничего не значат
*/
class Tile
{
public:
  //Конструкторы

  Tile();

  //Set методы

  void setHeight(float height);
  void setTemp(int temp);
  void setHumid(float humid);
  void setType(int type);

  //Get методы

  inline float Height() { return height_; }
  inline int Temperature() {return temperature_; }
  inline float Humidity() { return humidity_; } 
  inline short Type() { return type_; }

  //Деструктор по умолчанию

  ~Tile();

private:
  short type_;//Тип
  float height_;//Альтитуда от 0 до 1.
  int temperature_;//Температура в градусах цельсия, ограничена только снизу по очевидным причинам
  float humidity_;//Влажность. Выражается в нормальизованном виде от 0 до 1, где 0 - полная сухость.
};

