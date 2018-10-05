#include "stdafx.h"
#include "Terrain.h"


Terrain::Terrain()
  : d_heightGridStep(1.0f)
{
}


void Terrain::setHeightMap(HeightMap i_heightMap)
{
  d_heightMap = std::move(i_heightMap);
}
