#include "HeightGenerator.h"

void HeightGenerator::setRoughness(float roughness){
  roughness_ = (abs(roughness) > 1.0f) ? 1.0f : abs(roughness);
}

void HeightGenerator::setSurfacePerc(float surfacePerc){
  surfacePerc_ = (abs(surfacePerc) > 1.0f) ? 1.0f : abs(surfacePerc);
}

float HeightGenerator::square_displace(int i, int j) {
  float total = 0.0, avg;
  int quater_step = step_size/4;
  if (i - quater_step >= 0)
    total += getMap()[i - quater_step][j]->Height();
  else
    total += -1;

  if (i + quater_step < getMap().Height())
    total += getMap()[i + quater_step][j]->Height();
  else
    total += -1;

  if (j - quater_step >= 0)
    total += getMap()[i][j - quater_step]->Height();
  else
    total += -1;

  if (j + quater_step < getMap().Width())
    total += getMap()[i][j + quater_step]->Height();
  else
    total += -1;
  
  total = (total < 0.0f)? 0.0f : total;
  avg = total/4.0f;
  return curr_roughness *(float)(rand())/RAND_MAX + (1.0f - curr_roughness)*avg;
}

float HeightGenerator::diamond_displace(int i, int j) {
  // ul - - - - -  ur
  // |             |
  // |             |
  // | - - i,j - - |
  // |             |
  // |             |
  // ll - - - - - lr

  float avg = 0.0f,ul,ur,ll,lr;
  int quater_step = step_size / 4;
  ul = getMap()[i - quater_step][j - quater_step]->Height();
  ur = getMap()[i - quater_step][j + quater_step]->Height();
  ll = getMap()[i + quater_step][j - quater_step]->Height();
  lr = getMap()[i + quater_step][j + quater_step]->Height();
  avg = (ul + ur + ll + lr) / 4.0f;
  return curr_roughness * (float)(rand()) / RAND_MAX + (1.0f - curr_roughness) * avg;
}

void HeightGenerator::square() {
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = 0; i < getMap().Height(); i += half_step)
    for (int j = quater_step; j < getMap().Width(); j += half_step)
      getMap()[i][j]->setHeight(square_displace(i, j));
  for (int i = quater_step; i<getMap().Height(); i += half_step)
    for (int j = 0; j < getMap().Width(); j += half_step)
      getMap()[i][j]->setHeight(square_displace(i, j));
}

void HeightGenerator::diamond() {
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = quater_step; i<getMap().Height(); i += half_step)
    for (int j = quater_step; j<getMap().Width() - 1; j += half_step)
      getMap()[i][j]->setHeight(diamond_displace(i, j));
}

void HeightGenerator::generate() {
  int iterations;
  int Height = getMap().Height(), Width = getMap().Width();
  getMap()[0][0]->setHeight((float)(rand()) / RAND_MAX);
  getMap()[0][Width - 1]->setHeight((float)(rand()) / RAND_MAX);
  getMap()[Height - 1][0]->setHeight((float)(rand()) / RAND_MAX);
  getMap()[Height - 1][Width - 1]->setHeight((float)(rand()) / RAND_MAX);
  getMap()[0][(Width - 1) / 2]->setHeight((float)(rand()) / RAND_MAX);
  getMap()[Height - 1][(Width - 1) / 2]->setHeight((float)(rand()) / RAND_MAX);
  for (int i = 0; i < 15; i++)
    if (Height == pow(2, i) + 1) {
      iterations = i;
      break;
    }
  for (int i = 0; i < iterations; i++) {
    curr_roughness = pow(roughness_, i);
    step_size = ((Width - 1) / pow(2, i));
    if (i == 1) {
      getMap()[0][0]->setHeight(0.0f);
      getMap()[0][Width - 1]->setHeight(0.0f);
      getMap()[Height - 1][0]->setHeight(0.0f);
      getMap()[Height - 1][Width - 1]->setHeight(0.0f);
      getMap()[0][(Width - 1) / 2]->setHeight(0.0f);
      getMap()[Height - 1][(Width - 1) / 2]->setHeight(0.0f);
    }
    diamond();
    square();
  }
  smooth();
  createOcean();
  createMountains();
}

void HeightGenerator::smooth() {
  for (int i=0; i<getMap().Height(); i++)
    for (int j=0; j<getMap().Width();j++)
      getMap()[i][j]->setHeight(pow(getMap()[i][j]->Height(),2));
}


void HeightGenerator::createOcean() {
  int row = 100-int(surfacePerc_*100),collumn = (int)(roughness_*100);
  getMap().setSeaLevel(coeff[row][collumn] * getMap().avgHeight());
  for (int i=0;i<getMap().Height();i++)
    for (int j=0;j<getMap().Width();j++)
      if (getMap()[i][j]->Height() <= getMap().SeaLevel())
        getMap()[i][j]->setType(0);
}

void HeightGenerator::createMountains() {//Попробую маску 3х3
  float summ, max = getMap().maxHeight(), mountainLevel = (max - getMap().SeaLevel())*0.24f;
  int num; //Кол-во клеток суши внутри маски
  for (int i = 1; i < getMap().Height() - 1; i++) 
    for (int j = 1; j < getMap().Width() - 1; j++) {
      summ = 0.0f;
      num = 0;
      for (int k = i-1; k < i+2;k++){
        for (int n = j-1; n < j+2; n++)
          if (getMap()[k][n]->Height() > getMap().SeaLevel()) {
            summ += getMap()[k][n]->Height();
            num++;
          }
      }
      if ((float)(summ/num) - getMap().SeaLevel() > mountainLevel)
        getMap()[i][j]->setType(1);
    }
}

HeightGenerator::~HeightGenerator(){

}
