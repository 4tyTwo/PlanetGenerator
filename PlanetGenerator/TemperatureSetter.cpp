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
      heightDiff = (*map)[i][j]->Height() / heightStep; //�������� ����������� ��-�� ������� ������
      currTemp = (baseTemp - cordDiff - heightDiff)/(*map)[i][j]->Humidity();
      (*map)[i][j]->setTemp(currTemp);
    }
  }
}
