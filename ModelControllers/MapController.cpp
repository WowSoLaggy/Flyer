#include "stdafx.h"
#include "MapController.h"

#include <Model/Map.h>

MapController MapController::createNewMap()
{
  MapController mapController;
  return mapController;
}


MapController::MapController()
{
  d_map.reset(new Map());
}


void MapController::update(double i_dt)
{
}
