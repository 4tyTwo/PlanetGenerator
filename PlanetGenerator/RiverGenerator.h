#pragma once
#include "Map.h"
#include <time.h>
struct pt {
  int x, y;
};
struct pt_holder {
  pt start, finish;
};
class RiverGenerator
{
public:
  RiverGenerator();
  RiverGenerator(Map* map,int num) { data = map; number = num; std::vector<pt_holder> temp; coords = temp; }

  ~RiverGenerator();

  void generate(); //
  
  void generation(int base_x, int base_y, int x, int y, int& sign);
private:
  Map* data;
  int number;
  std::vector<pt_holder> coords;
  //Методы для рисования кривых рек
  void line(int x0, int y0, int x1, int y1); //Прямая линия из точки (x0;y0) в точку (x1;y1)
  void curve(int x0, int y0, int x1, int y1, int x2, int y2); //Кривая Безье  из точки (x0;y0) в точку (x2;y2) с управляющей точкой (x1;y1)
  void curveSeg(int x0, int y0, int x1, int y1, int x2, int y2); //Сегмент кривой Безье
  //Методы для обнаружения пересечения
  bool checkIntersect(int x0,int y0,int x1,int y1);
  inline int area(pt a, pt b, pt c) {return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);}
  bool intersect_1(int a, int b, int c, int d);
  bool intersect(pt a, pt b, pt c, pt d);
};

