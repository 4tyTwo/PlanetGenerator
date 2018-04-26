#pragma once
#include "Generator.h"
class BiomeGenerator : public Generator
{
public:
  BiomeGenerator(Map* data);
  static const float humidCoeffs[6], tempCoeffs[6];   //������������ ��� ������ ��������� � ������, �� ������ ���� �������������
  void generate();
  ~BiomeGenerator();
private:
  int placeZone(int tempZone, int humidZone);
  int temperatureZone(int curr); //���������� ����� ������������� ���� ��� �������� �����������
  int humidityZone(float curr); //���������� ����� ���� ��������� ��� ��������� curr
  bool between(float lower, float upper, float checked); //���������� true, ���� lower < cheched < upper
  float HumidBorders[6], TempBorders[6]; //������� 
};

