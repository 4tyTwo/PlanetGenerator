#include "TemperatureSetter.h"

/* Считаю, что разность между уровнем моря и высочайшей точкой карты - 10км (переделать)
    Каждый километр температура падает на 5 градусов
    За эту разность температура падает на 50 градусов
    Считаем высоту, на которой температура падает на 1 градус
    Для каждой клетки, что выше уровня моря считаем разность между ней и уровнем моря
    Делим разность на еденицу падения температуры
    Получаем итоговое снижение температуры от высоты
*/

/* Считаю что в среднем температура у полюсов: -33, а у экватора +26, но за читый перепад берем 50 градусов. Влажность и высота все же оказывают влияние*/

void TemperatureSetter::setTemperature(Map* map, int baseTemp) { //baseTemp - базовая температура экватора
  int equator = map->Height()/2,cordDiff,cordstep = map->Height()/100,currTemp; //Линия экватора, чем ближе, тем жарче, step - то, раз в сколько клеток температура уменьшается на градус
  float heightDiff, sealLevel = map->SeaLevel(), heightStep = (map->maxHeight() - sealLevel)/50; //Температурный коэффициент
  for (int i = 0; i < map->Height(); i++) {
    cordDiff = (abs(i - equator) / cordstep) * 0.6; //Снижение температуры из-за влияния широты
    for (int j = 0; j < map->Width(); j++) {
      heightDiff = (*map)[i][j]->Height() / heightStep; //Снижение температуры из-за влияния высоты
      currTemp = (baseTemp - cordDiff - heightDiff)/(*map)[i][j]->Humidity();
      (*map)[i][j]->setTemp(currTemp);
    }
  }
}
