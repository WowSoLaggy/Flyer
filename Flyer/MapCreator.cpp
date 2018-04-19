#include "stdafx.h"
#include "MapCreator.h"


Map MapCreator::createMap()
{
  Map map;

  GameObject player;
  player.position = { 10., 10. };
  map.d_objects.push_back(player);

  return map;
}
