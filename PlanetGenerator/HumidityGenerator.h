#pragma once
#include "Generator.h"
#include <cmath>
#include <limits>//��� is_equal
class HumidityGenerator: public Generator
{
public:
  //������������
  HumidityGenerator(Map* newdata, float roughness);
  inline HumidityGenerator() { roughness_ = 0.0f; }
  //Set ������
  //inline void setMap(Map newdata) { data = newdata; }
  void setRoughness(float rougness);

  //Get ������
  inline float roughness() { return roughness_; }
  //�������� ����� ��������� ����� �����
  void generate();
  void smooth(); //�������� ��� �������� ������ � ������� ��� ��������� ����� �������� ��������
                 //���������� ��-���������
  ~HumidityGenerator();

private:
  //���� ������ 
  float roughness_, curr_roughness; //Roughness - ��. �������� square-diamond ���������. surfecePerc - ������� ���� �� �����.
                                                  //Map* data; //�����, ������������ � �����
  int step_size;
  //��������� ������ ���������
  void square();
  void diamond();
  float square_displace(int i, int j);
  float diamond_displace(int i, int j);
};

