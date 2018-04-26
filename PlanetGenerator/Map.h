#pragma once
#include "Tile.h"
//���� ���� �������� ������ ���� ���� ������������ ������, ������ ���� � �.�. ��� ������� �����.
class Map
{
public:
  //�����������
  Map(int Height,int Width);
  Map();

  //Set ������
  void setSeaLevel(float sea);
  //Get ������
  inline int Height() { return Height_; }
  inline int Width() { return Width_; }
  inline float SeaLevel() { return SeaLevel_; }
  Tile* get(int x,int y); //�������� �� ������
  Tile** operator[](int x) { return data[x]; } //�������� ��� �� ������� ����

  //��������� ������
  float avgHeight(); //������� ������ �����
  float maxHeight(); //����� ������� ����� �����
  float maxHumidity();
  int maxTemperature(); 
  ~Map();
private:
  int Height_,Width_;
  float SeaLevel_;
  Tile ***data;
};

