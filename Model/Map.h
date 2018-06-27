#pragma once

#include "GameObject.h"

class Map final
{
public:

  Map();

private:

  std::vector<GameObject> d_gameObjects;

};
