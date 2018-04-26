#include "BiomeGenerator.h"

const float BiomeGenerator::tempCoeffs[6] = { 0.31f, 0.41f, 0.46f, 0.68f, 0.74f, 1.0f };
const float BiomeGenerator::humidCoeffs[6] = { 0.25f, 0.31f, 0.47f, 0.64f, 0.72f, 1.0f };

void BiomeGenerator::generate() {
  for (int i = 0; i < getMap().Height(); i++)
    for (int j = 0; j < getMap().Width(); j++) {
      if(getMap()[i][j]->Type() != 1 && getMap()[i][j]->Type() != 0 && getMap()[i][j]->Type() != 12)
        getMap()[i][j]->setType(placeZone(temperatureZone(getMap()[i][j]->Temperature()), humidityZone(getMap()[i][j]->Humidity())));
    }
}

int BiomeGenerator::placeZone(int tempZone, int humidZone) {
  //Очень некрасивый свитч
  switch (humidZone) {
    case 6: {
      if (tempZone >= 5)
        return 11; //Дождевые леса
      if (tempZone >= 3)
        return 7; //Лиственные леса
      else
        return 4; //Тайга
      }
    case 5: {
      if (tempZone >= 5)
        return 10; //Субтропический лес
      if (tempZone >= 3)
        return 7; //Лиственные леса
      else
        return 4; //Тайга
    }
    case 4: {
      if (tempZone >= 5)
        return 10; //Субтропический лес
      if (tempZone >= 3)
        return 7; //Лиственные леса
      if (tempZone == 2)
        return 4;
      else
        return 3; //Тундра
    }
    case 3: {
      if (tempZone == 6)
        return 9; //Саванна
      if (tempZone >= 4)
        return 6; //Степь
      else
        return 4;
    }
    case 2: {
      if (tempZone == 6)
        return 9; //Саванна
      if (tempZone >= 4)
        return 6; //Степь
      if (tempZone == 1)
        return 2;
      else
        return 5;
    }
    case 1: {
      if (tempZone == 6)
        return 8; //Пустыня
      if (tempZone >=4)
        return 6; // Степь
      if (tempZone == 1)
        return 2; //Арктическая пустыня
      else
        return 5;//Субарктический климат
    }
    default:
      return -1;//Нонсенс
  }
}

BiomeGenerator::BiomeGenerator(Map* data) {
  setMap(data);
  float maxHumid = getMap().maxHumidity(), maxTemp = getMap().maxTemperature();
  for (int i = 0; i < 6; i++) {
    HumidBorders[i] = maxHumid * humidCoeffs[i];
    TempBorders[i] = maxTemp * tempCoeffs[i];
  }
}

int BiomeGenerator::temperatureZone(int curr) {
  if (between(0,TempBorders[1],curr))
    return 1;
  for ( int i = 1; i < 6; i++ )
    if (between(TempBorders[i-1],TempBorders[i],curr))
      return i+1;
}

int BiomeGenerator::humidityZone(float curr) {
  if (between(0, HumidBorders[1], curr))
    return 1;
  for (int i = 1; i < 6; i++)
    if (between(HumidBorders[i - 1], HumidBorders[i], curr))
      return i + 1;
}

bool BiomeGenerator::between(float lower, float upper, float checked)
{
  if (lower < checked && upper > checked)
    return true;
  return false;
}

BiomeGenerator::~BiomeGenerator(){
}
