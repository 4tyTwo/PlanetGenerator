#include "HumiditySetter.h"
//���� ������� ��� �� ����� ��������� �����, �� ������ ��
//���� ��������� ������ �� ����� � ���� ��������, ��� �� ����� � ���������� ���� (� ������� ������� � ������ ����) �� ����� �������� ������� �����
/*������ ������ � ����� ����� ��������� 1 � ��������� ������� �� �������� ������*/

//���� ���� ��������� ��� ��, ��� ��������, �� ��������
void HumiditySetter::setHumidity(Map* map) {
    std::string water = "water", mountain = "mountain";
    int finishHoriz, finishVert, radius=map->Width()/20; //����� ������ ��� ��������
    float humidity, level = map->SeaLevel() * 0.92, seaLevel = map->SeaLevel();
    for (int i = 0; i < map->Height(); i++) {
      for (int j = 0; j < map->Width(); j++) {
        if ((*map)[i][j]->Height() <= seaLevel) {
          (*map)[i][j]->setHumid(1.0f);
          if ((*map)[i][j]->Height() > level){
            //���� �����-����, �����-������ � ����������� ������������� ������ �� ��������� ��������, ������ ��������� 100
            //�� ������ ������
            finishHoriz = (j-radius >= 0) ? j- radius : 0;
            for (int m = j; m > finishHoriz && (*map)[i][m]->Type().compare(mountain);m--){ //���� �� ������� ������� ��� �� ��������� �� ����
                if ((*map)[i][m]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - j) / radius * 5; //���� ����� ��� ��������������
                else
                  humidity = (0.2f - abs(m - j) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
            }
            //�� ������ ������
            finishHoriz = (j + radius < map->Width()) ? j + radius : map->Width()-1;
            for (int m = j; m < finishHoriz && (*map)[i][m]->Type().compare(mountain); m++) { //���� �� ������� ������� ��� �� ��������� �� ����
              if ((*map)[i][m]->Type().compare(water)){
                if ((*map)[i][m]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - j) / radius * 5; //���� ����� ��� ��������������
                else
                  humidity = (0.2f - abs(m - j) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
              }
            }
            //�� ������ �����
            finishVert = (i - radius >= 0) ? i - radius : 0;
            for (int m = i; m > finishVert && (*map)[m][j]->Type().compare(mountain); m--) { //���� �� ������� ������� ��� �� ��������� �� ����
              if ((*map)[m][j]->Type().compare(water)) {
                if ((*map)[m][j]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - i) / radius * 5; //���� ����� ��� ��������������
                else
                  humidity = (0.2f - abs(m - i) / radius * 5) * (seaLevel / (*map)[m][j]->Height());
              }
             }
            //�� ������ ������
            finishVert = (i + radius < map->Height()) ? i + radius : map->Height() - 1;
            for (int m = i; m < finishVert; m++) { //���� �� ������� ������� ��� �� ��������� �� ����
              if ((*map)[m][j]->Type().compare(water)){
                if ((*map)[m][j]->Type().compare(mountain))
                  humidity = 0.2f - abs(m - i) / radius * 5; //���� ����� ��� ��������������
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