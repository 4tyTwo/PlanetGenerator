#include "BiomeGenerator.h"

const float BiomeGenerator::tempCoeffs[6] = { 0.31f, 0.41f, 0.46f, 0.68f, 0.74f, 1.0f };
const float BiomeGenerator::humidCoeffs[6] = { 0.25f, 0.31f, 0.47f, 0.64f, 0.72f, 1.0f };

void BiomeGenerator::generate() {

}

int BiomeGenerator::placeZone(int tempZone, int humidZone) {
  return -1;
}

BiomeGenerator::BiomeGenerator(){
  float maxHumid = getMap().maxHumidity(), maxTemp = getMap().maxTemperature();
  for (int i = 0; i < 6; i++) {
    HumidBorders[i] = maxHumid * humidCoeffs[i];
    TempBorders[i] = maxTemp * tempCoeffs[i];
  }
}

int BiomeGenerator::temperatureZone(float curr) {
  if (between(0,TempBorders[1],curr))
    return 1;
  for ( int i = 1; i < 6; i++ )
    if (between(TempBorders[i-1],TempBorders[i],curr))
      return i+1;
}

int BiomeGenerator::humidityZone(float curr) {
  if (between(0, HumidBorders[1], curr))
    return 1;
  for (int i = 1; i < 6; i++)
    if (between(HumidBorders[i - 1], HumidBorders[i], curr))
      return i + 1;
}

bool BiomeGenerator::between(float lower, float upper, float checked)
{
  if (lower < checked && upper > checked)
    return true;
  return false;
}

BiomeGenerator::~BiomeGenerator(){
}
