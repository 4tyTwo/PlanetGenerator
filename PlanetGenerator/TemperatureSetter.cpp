#include "TemperatureSetter.h"

/* ������, ��� �������� ����� ������� ���� � ���������� ������ ����� - 10�� (����������)
    ������ �������� ����������� ������ �� 5 ��������
    �� ��� �������� ����������� ������ �� 50 ��������
    ������� ������, �� ������� ����������� ������ �� 1 ������
    ��� ������ ������, ��� ���� ������ ���� ������� �������� ����� ��� � ������� ����
    ����� �������� �� ������� ������� �����������
    �������� �������� �������� ����������� �� ������
*/

/* ������ ��� � ������� ����������� � �������: -33, � � �������� +26, �� �� ����� ������� ����� 50 ��������. ��������� � ������ ��� �� ��������� �������*/

void TemperatureSetter::setTemperature(Map* map, int baseTemp) { //baseTemp - ������� ����������� ��������
  int equator = map->Height()/2,cordDiff,cordstep = map->Height()/100,currTemp; //����� ��������, ��� �����, ��� �����, step - ��, ��� � ������� ������ ����������� ����������� �� ������
  float heightDiff, sealLevel = map->SeaLevel(), heightStep = (map->maxHeight() - sealLevel)/50; //������������� �����������
  for (int i = 0; i < map->Height(); i++) {
    cordDiff = (abs(i - equator) / cordstep) * 0.6; //�������� ����������� ��-�� ������� ������
    for (int j = 0; j < map->Width(); j++) {
      if ((*map)[i][j]->Height() > sealLevel)
        heightDiff = ((*map)[i][j]->Height()-sealLevel) / heightStep; //�������� ����������� ��-�� ������� ������
      else
        heightDiff = 0.0f;
      currTemp = (baseTemp - cordDiff - heightDiff) / (1.0f + (*map)[i][j]->Humidity()/2);
      (*map)[i][j]->setTemp(currTemp);
    }
  }
}
