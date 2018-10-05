#pragma once


class HeightMap
{
public:

  HeightMap();

  int getSizeX() const { return d_sizeX; }
  int getSizeZ() const { return d_sizeZ; }

  void resize(int i_sizeX, int i_sizeZ, float i_defaultHeight);

  void setHeight(int i_x, int i_z, float i_height);
  float getHeight(int i_x, int i_z);

private:

  int d_sizeX;
  int d_sizeZ;

  std::vector<float> d_points;

};
