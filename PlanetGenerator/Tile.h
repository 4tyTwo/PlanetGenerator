#pragma once
#include <algorithm>
#include <vector>
/* 
    ����:
    0 - ����
    1 - ����
    2 - ����������� �������
    3 - ������
    4 - �����
    5- ����������
    6 - �����
    7 - ���
    8 - �������
    9 - �������
    10 - �������������� ���
    11 - �������� ���
    ��������� - ������ �� ������
*/
class Tile
{
public:
  //������������

  Tile();

  //Set ������

  void setHeight(float height);
  void setTemp(int temp);
  void setHumid(float humid);
  void setType(int type);

  //Get ������

  inline float Height() { return height_; }
  inline int Temperature() {return temperature_; }
  inline float Humidity() { return humidity_; } 
  inline short Type() { return type_; }

  //���������� �� ���������

  ~Tile();

private:
  short type_;//���
  float height_;//��������� �� 0 �� 1.
  int temperature_;//����������� � �������� �������, ���������� ������ ����� �� ��������� ��������
  float humidity_;//���������. ���������� � ���������������� ���� �� 0 �� 1, ��� 0 - ������ �������.
};

