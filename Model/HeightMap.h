#pragma once


class HeightMap
{
public:

  HeightMap();

  int getSizeX() const { return d_sizeX; }
  int getSizeZ() const { return d_sizeZ; }

  int getSizeXInc() const { return d_sizeXInc; }
  int getSizeZInc() const { return d_sizeZInc; }

  void resize(int i_sizeX, int i_sizeZ, float i_defaultHeight);

  void setHeight(int i_x, int i_z, float i_height);
  float getHeight(int i_x, int i_z) const;

private:

  int d_sizeX;
  int d_sizeZ;

  int d_sizeXInc;
  int d_sizeZInc;

  std::vector<float> d_points;

};
