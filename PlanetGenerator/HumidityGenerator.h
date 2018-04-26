#pragma once
#include "Generator.h"
#include <cmath>
#include <limits>//Для is_equal
class HumidityGenerator: public Generator
{
public:
  //Конструкторы
  HumidityGenerator(Map* newdata, float roughness);
  inline HumidityGenerator() { roughness_ = 0.0f; }
  //Set методы
  //inline void setMap(Map newdata) { data = newdata; }
  void setRoughness(float rougness);

  //Get методы
  inline float roughness() { return roughness_; }
  //Основной метод генерации карты высот
  void generate();
  void smooth(); //Возводит все значения высоты в квадрат для получения более плавного перехода
                 //Деструктор по-умолчанию
  ~HumidityGenerator();

private:
  //Поля класса 
  float roughness_, curr_roughness; //Roughness - см. описание square-diamond алгоритма. surfecePerc - процент суши на карте.
                                                  //Map* data; //Карта, передаваемая в класс
  int step_size;
  //Служебные методы генерации
  void square();
  void diamond();
  float square_displace(int i, int j);
  float diamond_displace(int i, int j);
};

