#pragma once
#include "Tile.h"
class Map
{
public:
  //�����������
  Map(int x_size,int y_size);
  Map();

  //Get �������
  inline int x_size() { return x_size_; }
  inline int y_size() { return y_size_; }
  Tile* get(int x,int y); //�������� �� ������
  Tile** operator[](int x) { return data[x]; } //�������� ��� �� ������� ����

  //��������� �������
  float avgHeight(); //������� ������ �����
  
  ~Map();
private:
  int x_size_,y_size_;
  Tile ***data;
};

