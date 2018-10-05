#include "stdafx.h"
#include "HeightMap.h"


HeightMap::HeightMap()
  : d_sizeX(0)
  , d_sizeZ(0)
{
}

void HeightMap::resize(int i_sizeX, int i_sizeZ, float i_defaultHeight)
{
  d_sizeX = i_sizeX;
  d_sizeZ = i_sizeZ;

  d_points.resize(d_sizeX * d_sizeZ, i_defaultHeight);
}


void HeightMap::setHeight(int i_x, int i_z, float i_height)
{
  int index = i_x + i_z * d_sizeX;

  if (index < 0 || d_sizeX * d_sizeZ <= index)
    throw std::runtime_error("Pars are out of bounds.");

  d_points[index] = i_height;
}

float HeightMap::getHeight(int i_x, int i_z) const
{
  int index = i_x + i_z * d_sizeX;

  if (index < 0 || d_sizeX * d_sizeZ <= index)
    throw std::runtime_error("Pars are out of bounds.");

  return d_points[index];
}
