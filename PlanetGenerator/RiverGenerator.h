#pragma once
#include "Map.h"
class RiverGenerator
{
public:
  RiverGenerator();

  ~RiverGenerator();

  void generate(); //
  void generation(int base_x, int base_y, int x, int y, int& sign);
private:
  Map* data;
  int number;
  //Функции для рисования кривых рек
  void line(int x0, int y0, int x1, int y1); //Прямая линия из точки (x0;y0) в точку (x1;y1)
  void curve(int x0, int y0, int x1, int y1, int x2, int y2); //Кривая Безье  из точки (x0;y0) в точку (x2;y2) с управляющей точкой (x1;y1)
  void curveSeg(int x0, int y0, int x1, int y1, int x2, int y2); //Сегмент кривой Безье
};

