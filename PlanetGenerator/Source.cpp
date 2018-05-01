#include <iostream>
#include <Windows.h>
#include "HeightGenerator.h"
#include <time.h>
#include <iostream>
#include <chrono>
#include <algorithm>
#include "RiverGenerator.h"
#include "TemperatureSetter.h"
#include "HumidityGenerator.h"
#include "BiomeGenerator.h"
#include "MapDrawer.h"
using namespace std::chrono;

int main() {
  srand(time(NULL));
  high_resolution_clock::time_point t1 = high_resolution_clock::now(), t2, t3, t4;
  Map *testmap = new Map(1025, 2049);
  HeightGenerator generator(testmap, 0.47f, 0.32f);
  generator.generate();
  RiverGenerator rivergenerator(testmap, 10);
  rivergenerator.generate();
  HumidityGenerator humgenerator(testmap,0.3f);
  humgenerator.generate();
  TemperatureSetter::setTemperature(testmap,33);
  BiomeGenerator biomegen(testmap);
  biomegen.generate();
  MapDrawer drawer(testmap);
  drawer.drawPhysicalMap("C:\\Output\\Map.png");
  drawer.drawHumidMap("C:\\Output\\HumidMap.png");
  drawer.drawTempMap("C:\\Output\\TempMap.png");
  drawer.drawBiomeMap("C:\\Output\\BiomeMap.png");
  testmap->~Map();
  return 0;
}