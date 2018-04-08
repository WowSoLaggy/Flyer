#include "stdafx.h"
#include "MapCreator.h"


Map MapCreator::createMap()
{
  Map map;

  GameObject playerPlane;
  playerPlane.position = { 10., 10. };
  map.d_objects.push_back(playerPlane);

  return map;
}
