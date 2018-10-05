#pragma once

#include "HeightMap.h"


class Terrain
{
public:

  Terrain();

  void setTextureName(const std::string& i_textureName) { d_textureName = i_textureName; }
  const std::string& getTextureName() const { return d_textureName; }

  void setHeightGridStep(float i_step) { d_heightGridStep = i_step; }
  float getHeightGridStep() const { return d_heightGridStep; }

  void setHeightMap(HeightMap i_heightMap);
  const HeightMap& getHeightMap() const { return d_heightMap; }

  float getSizeX() const { return d_heightMap.getSizeX() * d_heightGridStep; }
  float getSizeZ() const { return d_heightMap.getSizeZ() * d_heightGridStep; }

private:

  std::string d_textureName;

  float d_heightGridStep;
  HeightMap d_heightMap;

};
