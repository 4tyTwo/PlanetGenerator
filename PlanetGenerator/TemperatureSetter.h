#pragma once
#include "Map.h"
//����������� �����, ������� ��� ������ ������������ ������ ����� �������� ����������� ������ ���������� �����
//����������� - ������� �� ������, ��������� � ����������
class TemperatureSetter
{
public:
  static void setTemperature(Map* map, int baseTemp);
  virtual ~TemperatureSetter() = 0;
};

