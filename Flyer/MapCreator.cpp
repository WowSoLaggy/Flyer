#include "stdafx.h"
#include "MapCreator.h"


Map MapCreator::createMap()
{
  Map map;

  GameObject player;
  player.setPosition({ 5.0f, 5.0f, 0.0f });
  map.d_objects.push_back(player);

  return map;
}
