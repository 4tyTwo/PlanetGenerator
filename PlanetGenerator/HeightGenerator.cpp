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
    total += (*data)[i - quater_step][j]->Height();
  else
    total += -1;

  if (i + quater_step < data->x_size())
    total += (*data)[i + quater_step][j]->Height();
  else
    total += -1;

  if (j - quater_step >= 0)
    total += (*data)[i][j - quater_step]->Height();
  else
    total += -1;

  if (j + quater_step < data->y_size())
    total += (*data)[i][j + quater_step]->Height();
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
  ul = (*data)[i - quater_step][j - quater_step]->Height();
  ur = (*data)[i - quater_step][j + quater_step]->Height();
  ll = (*data)[i + quater_step][j - quater_step]->Height();
  lr = (*data)[i + quater_step][j + quater_step]->Height();
  avg = (ul + ur + ll + lr) / 4.0f;
  return curr_roughness * (float)(rand()) / RAND_MAX + (1.0f - curr_roughness) * avg;
}

void HeightGenerator::square() {
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = 0; i < data->x_size(); i += half_step)
    for (int j = quater_step; j < data->y_size(); j += half_step)
      (*data)[i][j]->setHeight(square_displace(i, j));
  for (int i = quater_step; i<data->x_size(); i += half_step)
    for (int j = 0; j < data->y_size(); j += half_step)
      (*data)[i][j]->setHeight(square_displace(i, j));
}

void HeightGenerator::diamond() {
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = quater_step; i<data->x_size(); i += half_step)
    for (int j = quater_step; j<data->y_size() - 1; j += half_step)
      (*data)[i][j]->setHeight(diamond_displace(i, j));
}

void HeightGenerator::generate() {
  int iterations;
  int x_size = data->x_size(), y_size = data->y_size();
  (*data)[0][0]->setHeight((float)(rand()) / RAND_MAX);
  (*data)[0][y_size - 1]->setHeight((float)(rand()) / RAND_MAX);
  (*data)[x_size - 1][0]->setHeight((float)(rand()) / RAND_MAX);
  (*data)[x_size - 1][y_size - 1]->setHeight((float)(rand()) / RAND_MAX);
  (*data)[0][(y_size - 1) / 2]->setHeight((float)(rand()) / RAND_MAX);
  (*data)[x_size - 1][(y_size - 1) / 2]->setHeight((float)(rand()) / RAND_MAX);
  for (int i = 0; i < 15; i++)
    if (x_size == pow(2, i) + 1) {
      iterations = i;
      break;
    }
  for (int i = 0; i < iterations; i++) {
    curr_roughness = pow(roughness_, i);
    step_size = ((y_size - 1) / pow(2, i));
    if (i == 1) {
      (*data)[0][0]->setHeight(0.0f);
      (*data)[0][y_size - 1]->setHeight(0.0f);
      (*data)[x_size - 1][0]->setHeight(0.0f);
      (*data)[x_size - 1][y_size - 1]->setHeight(0.0f);
      (*data)[0][(y_size - 1) / 2]->setHeight(0.0f);
      (*data)[x_size - 1][(y_size - 1) / 2]->setHeight(0.0f);
    }
    diamond();
    square();
  }
  smooth();
  createOcean();
}

void HeightGenerator::smooth() {
  for (int i=0; i<data->x_size(); i++)
    for (int j=0; j<data->y_size();j++)
      (*data)[i][j]->setHeight(pow((*data)[i][j]->Height(),2));
}


void HeightGenerator::createOcean() {
  std::string type = "water";
  int row = 100-int(surfacePerc_*100),collumn = (int)(roughness_*100);
  float sea_level = coeff[row][collumn] * data->avgHeight();
  for (int i=0;i<data->x_size();i++)
    for (int j=0;j<data->y_size();j++)
      if ((*data)[i][j]->Height() <= sea_level)
        (*data)[i][j]->setType(type);
}


HeightGenerator::~HeightGenerator(){

}
