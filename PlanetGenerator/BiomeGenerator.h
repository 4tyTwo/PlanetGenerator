#pragma once
#include "Generator.h"
class BiomeGenerator : public Generator
{
public:
  BiomeGenerator(Map* data);
  static const float humidCoeffs[6], tempCoeffs[6];   //Коэффициенты для биомов подобраны в ручную, на основе моих представлений
  void generate();
  ~BiomeGenerator();
private:
  int placeZone(int tempZone, int humidZone);
  int temperatureZone(int curr); //Возвращает номер температурной зоны для заданной температуры
  int humidityZone(float curr); //Возвращает номер зоны влажности для влажности curr
  bool between(float lower, float upper, float checked); //Возвращает true, если lower < cheched < upper
  float HumidBorders[6], TempBorders[6]; //Границы 
};

