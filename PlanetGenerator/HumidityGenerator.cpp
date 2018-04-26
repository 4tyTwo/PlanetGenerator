#include "HumidityGenerator.h"

bool is_equal(double x, double y) {
  return std::fabs(x - y) < std::numeric_limits<double>::epsilon();
}

void HumidityGenerator::setRoughness(float roughness) {
  roughness_ = (abs(roughness) > 1.0f) ? 1.0f : abs(roughness);
}

float HumidityGenerator::square_displace(int i, int j) {
  float total = 0.0, avg, seaLevel = getMap().SeaLevel();
  int quater_step = step_size / 4;
  if (i - quater_step >= 0)
      total += getMap()[i - quater_step][j]->Humidity();
  else
    total += -1;

  if (i + quater_step < getMap().Height())
      total += getMap()[i + quater_step][j]->Humidity();
  else
    total += -1;

  if (j - quater_step >= 0)
      total += getMap()[i][j - quater_step]->Humidity();
  else
    total += -1;

  if (j + quater_step < getMap().Width())
      total += getMap()[i][j + quater_step]->Humidity();
  else
    total += -1;

  total = (total < 0.0f) ? 0.0f : total;
  avg = total / 4.0f;
  return curr_roughness * (float)(rand()) / RAND_MAX + (1.0f - curr_roughness)*avg;
}

float HumidityGenerator::diamond_displace(int i, int j) {
  // ul - - - - -  ur
  // |             |
  // |             |
  // | - - i,j - - |
  // |             |
  // |             |
  // ll - - - - - lr

  float avg = 0.0f, ul, ur, ll, lr, seaLevel = getMap().SeaLevel();
  int quater_step = step_size / 4;
    ul = getMap()[i - quater_step][j - quater_step]->Humidity();
    ur = getMap()[i - quater_step][j - quater_step]->Humidity();
    ll = getMap()[i + quater_step][j - quater_step]->Humidity();
    lr = getMap()[i + quater_step][j + quater_step]->Humidity();
  avg = (ul + ur + ll + lr) / 4.0f;
  return curr_roughness * (float)(rand()) / RAND_MAX + (1.0f - curr_roughness) * avg;
}

void HumidityGenerator::square() {
  float seaLevel = getMap().SeaLevel();
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = 0; i < getMap().Height(); i += half_step)
    for (int j = quater_step; j < getMap().Width(); j += half_step)
      if (getMap()[i][j]->Height() > seaLevel)
        getMap()[i][j]->setHumid(square_displace(i, j));
  for (int i = quater_step; i<getMap().Height(); i += half_step)
    for (int j = 0; j < getMap().Width(); j += half_step)
      if (getMap()[i][j]->Height() > seaLevel)
        getMap()[i][j]->setHumid(square_displace(i, j));
}

void HumidityGenerator::diamond() {
  float seaLevel = getMap().SeaLevel();
  int half_step = step_size / 2, quater_step = step_size / 4;
  for (int i = quater_step; i<getMap().Height(); i += half_step)
    for (int j = quater_step; j<getMap().Width() - 1; j += half_step)
      if (getMap()[i][j]->Height() > seaLevel)
        getMap()[i][j]->setHumid(diamond_displace(i, j));
}

void HumidityGenerator::generate() {
  int iterations;
  int Height = getMap().Height(), Width = getMap().Width();
  if (!is_equal(getMap()[0][0]->Humidity(),0.0f))
    getMap()[0][0]->setHumid((float)(rand()) / RAND_MAX);
  if (!is_equal(getMap()[0][Width - 1]->Humidity(), 0.0f))
    getMap()[0][Width - 1]->setHumid((float)(rand()) / RAND_MAX);
  if (!is_equal(getMap()[Height - 1][0]->Humidity(), 0.0f))
    getMap()[Height - 1][0]->setHumid((float)(rand()) / RAND_MAX);
  if (!is_equal(getMap()[Height - 1][Width - 1]->Humidity(), 0.0f))
    getMap()[Height - 1][Width - 1]->setHumid((float)(rand()) / RAND_MAX);
  if (!is_equal(getMap()[0][(Width - 1) / 2]->Humidity(), 0.0f))
    getMap()[0][(Width - 1) / 2]->setHumid((float)(rand()) / RAND_MAX);
  if (!is_equal(getMap()[Height - 1][(Width - 1) / 2]->Humidity(), 0.0f))
    getMap()[Height - 1][(Width - 1) / 2]->setHumid((float)(rand()) / RAND_MAX);

  for (int i = 0; i < 15; i++)
    if (Height == pow(2, i) + 1) {
      iterations = i;
      break;
    }
  for (int i = 0; i < iterations; i++) {
    curr_roughness = pow(roughness_, i);
    step_size = ((Width - 1) / pow(2, i));
    diamond();
    square();
  }
  smooth();
}

HumidityGenerator::HumidityGenerator(Map * newdata, float roughness){
  setMap(newdata); setRoughness(roughness);
  std::string water = "water";
  for (int i = 0; i < getMap().Height(); i++)
    for (int j = 0; j < getMap().Width(); j++)
      if (!getMap()[i][j]->Type().compare(water))
        getMap()[i][j]->setHumid(1.0f);
}


void HumidityGenerator::smooth() {
  for (int i = 0; i<getMap().Height(); i++)
    for (int j = 0; j<getMap().Width(); j++)
      getMap()[i][j]->setHumid(pow(getMap()[i][j]->Humidity(), 2));
}

HumidityGenerator::~HumidityGenerator()
{
}
