#pragma once
#include <SFML\Graphics.hpp>
#include "Generator.h"
class MapDrawer : public Generator
{
public:
  MapDrawer();
  inline MapDrawer(Map* map) { setMap(map); }
  void generate();
  void drawPhysicalMap(const std::string &filename);
  ~MapDrawer();
};

