#pragma once
#include "Map.h"
#include "coefficients.cpp"
#include <random>
class HeightGenerator
{
//������ ����� �������� ������� ������ (�����) � ����������� ������� ����� ������
//��� ����� �������� ����� �����.
public:
  //������������
  inline HeightGenerator(Map* newdata, float roughness, float surfacePerc) { data = newdata; setRoughness(roughness); setSurfacePerc(surfacePerc); }
  inline HeightGenerator() { roughness_ = 0.0; surfacePerc_ = 0.0;  }
  //Set ������
  //inline void setMap(Map newdata) { data = newdata; }
  void setRoughness(float rougness);
  void setSurfacePerc(float surfacePerc);
  void setSeaLevel(float seaLevel);

  //Get ������
  inline float roughness() { return roughness_; }
  inline float surfacePercentage() { return surfacePerc_; }
  inline float seaLevel() { return seaLevel_; }
  inline Map*  getMap() { return data; } 

  //�������� ����� ��������� ����� �����
  void generate();
  void smooth(); //�������� ��� �������� ������ � ������� ��� ��������� ����� �������� ��������
  //���������� ��-���������
  ~HeightGenerator();

private:
  //���� ������ 
  float roughness_, surfacePerc_, seaLevel_, curr_roughness; //Roughness - ��. �������� square-diamond ���������. surfecePerc - ������� ���� �� �����.
  Map* data; //�����, ������������ � �����
  int step_size;
  //��������� ������ ���������
  void square();
  void diamond();
  float square_displace(int i, int j);
  float diamond_displace(int i,int j);
  void createMountains(); //����� 3�3 ��������
  
  void createOcean(); //���������� � ������� �������������� ������������� ��� ��������� ������������ ������ ����
};

