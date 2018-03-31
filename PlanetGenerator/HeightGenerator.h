#pragma once
#include "Map.h"
#include "coefficients.cpp"
#include <random>
class HeightGenerator
{
//Данный класс получает матрицу тайлов (карту) и присваивает каждому тайлу высоту
//тем самым создавая карту высот.
public:
  //Конструкторы
  inline HeightGenerator(Map* newdata, float roughness, float surfacePerc) { data = newdata; setRoughness(roughness); setSurfacePerc(surfacePerc); }
  inline HeightGenerator() { roughness_ = 0.0; surfacePerc_ = 0.0;  }
  //Set методы
  //inline void setMap(Map newdata) { data = newdata; }
  void setRoughness(float rougness);
  void setSurfacePerc(float surfacePerc);
  void setSeaLevel(float seaLevel);

  //Get методы
  inline float roughness() { return roughness_; }
  inline float surfacePercentage() { return surfacePerc_; }
  inline float seaLevel() { return seaLevel_; }
  inline Map*  getMap() { return data; } 

  //Основной метод генерации карты высот
  void generate();
  void smooth(); //Возводит все значения высоты в квадрат для получения более плавного перехода
  //Деструктор по-умолчанию
  ~HeightGenerator();

private:
  //Поля класса 
  float roughness_, surfacePerc_, seaLevel_, curr_roughness; //Roughness - см. описание square-diamond алгоритма. surfecePerc - процент суши на карте.
  Map* data; //Карта, передаваемая в класс
  int step_size;
  //Служебные матоды генерации
  void square();
  void diamond();
  float square_displace(int i, int j);
  float diamond_displace(int i,int j);
  void createMountains(); //Маска 3х3 проходит
  
  void createOcean(); //Обращается к массиву предзаписанных коэффициентов для получения необходимого уровня воды
};

