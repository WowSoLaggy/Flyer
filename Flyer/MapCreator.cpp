#include "stdafx.h"
#include "MapCreator.h"


Map MapCreator::createMap()
{
  Map map;

  GameObject tree;
  tree.setPosition({ 5.0f, 5.0f, 0.0f });
  tree.setResourceNames(L"Data\\Tree", L"Data\\Blank.dds");
  map.d_objects.push_back(tree);

  GameObject player;
  player.setPosition({ 0.0f, 0.0f, 0.0f });
  player.setResourceNames(L"Data\\Player", L"Data\\Blank.dds");
  map.d_objects.push_back(player);

  return map;
}
