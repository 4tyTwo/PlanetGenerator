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
  //������� ��� ��������� ������ ���
  void line(int x0, int y0, int x1, int y1); //������ ����� �� ����� (x0;y0) � ����� (x1;y1)
  void curve(int x0, int y0, int x1, int y1, int x2, int y2); //������ �����  �� ����� (x0;y0) � ����� (x2;y2) � ����������� ������ (x1;y1)
  void curveSeg(int x0, int y0, int x1, int y1, int x2, int y2); //������� ������ �����
};

