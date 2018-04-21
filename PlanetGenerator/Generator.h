#pragma once
#include "Map.h"
class Generator
{
public:
  Generator();
  inline virtual Map& getMap() final {return *data_;}
  inline virtual void setMap(Map* data) final {data_ = data;}
  virtual void generate() = 0;
  ~Generator();
 private:
  Map *data_;
};

