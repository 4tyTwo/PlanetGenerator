#include "HumiditySetter.h"
//ЕСЛИ СДЕЛАТЬ ТАК ТО БУДЕТ ЖУУУУУТКО ДОЛГО, ЧО ДЕЛАТЬ ТО
//Если разделить клетки на океан и море например, или на окена и прибрежные зоны (с высотой близкой к уровню моря) то можно скипнуть бОльшую часть
/*Каждая клетка с водой имеет влажность 1 и оказывает влияние на соседние клетки*/

//Пока реки считаются так же, это проблема, но решаемая
void HumiditySetter::setHumidity(Map* map) {
    std::string water = "water", mountain = "mountain";
    int finishHoriz, finishVert, radius=map->Width()/20; //Точки старта для движения
    float humidity, level = map->SeaLevel() * 0.92, seaLevel = map->SeaLevel();
    for (int i = 0; i < map->Height(); i++) {
      for (int j = 0; j < map->Width(); j++) {
        if ((*map)[i][j]->Height() <= seaLevel) {
          (*map)[i][j]->setHumid(1.0f);
          if ((*map)[i][j]->Height() > level){
            //Идем вверх-вниз, влево-вправо и увеличиваем увлажненность клетки на небольшое значение, радиус попробуем 100
            //Из центра налево
            finishHoriz = (j-radius >= 0) ? j- radius : 0;
            for (int m = j; m > finishHoriz && (*map)[i][m]->Type().compare(mountain);m--){ //Пока не пройдем строчку или не напоримся на гору
                if ((*map)[i][m]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - j) / radius * 5; //Пока гадаю над коэффициентами
                else
                  humidity = (0.2f - abs(m - j) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
            }
            //Из центра вправо
            finishHoriz = (j + radius < map->Width()) ? j + radius : map->Width()-1;
            for (int m = j; m < finishHoriz && (*map)[i][m]->Type().compare(mountain); m++) { //Пока не пройдем строчку или не напоримся на гору
              if ((*map)[i][m]->Type().compare(water)){
                if ((*map)[i][m]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - j) / radius * 5; //Пока гадаю над коэффициентами
                else
                  humidity = (0.2f - abs(m - j) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
              }
            }
            //Из центра вверх
            finishVert = (i - radius >= 0) ? i - radius : 0;
            for (int m = i; m > finishVert && (*map)[m][j]->Type().compare(mountain); m--) { //Пока не пройдем строчку или не напоримся на гору
              if ((*map)[m][j]->Type().compare(water)) {
                if ((*map)[m][j]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - i) / radius * 5; //Пока гадаю над коэффициентами
                else
                  humidity = (0.2f - abs(m - i) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
              }
             }
            //Из центра вправо
            finishVert = (i + radius < map->Height()) ? i + radius : map->Height() - 1;
            for (int m = i; m < finishVert; m++) { //Пока не пройдем строчку или не напоримся на гору
              if ((*map)[m][j]->Type().compare(water)){
                if ((*map)[m][j]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - i) / radius * 5; //Пока гадаю над коэффициентами
                else
                  humidity = (0.2f - abs(m - i) / radius * 5) * (seaLevel/(*map)[m][j]->Height());
              (*map)[m][j]->setHumid(humidity);
              }
            }
          }
        }
      }
    }
}