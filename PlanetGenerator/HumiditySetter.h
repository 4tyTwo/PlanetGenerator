#pragma once
#include "Map.h"
class HumiditySetter
{
public:
  static void setHumidity(Map* map);
  virtual ~HumiditySetter() = 0;
};

