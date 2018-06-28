#pragma once


class Terrain
{
public:

  void setHeight(float i_height) { d_height = i_height; }
  float getHeight() const { return d_height; }

  void setSizeX(float i_sizeX) { d_sizeX = i_sizeX; }
  float getSizeX() const { return d_sizeX; }

  void setSizeZ(float i_sizeZ) { d_sizeZ = i_sizeZ; }
  float getSizeZ() const { return d_sizeZ; }

private:

  float d_sizeX;
  float d_sizeZ;
  float d_height;

};
