#pragma once


class Terrain
{
public:

  void setModelName(const std::string& i_modelName) { d_modelName = i_modelName; }
  const std::string& getModelName() const { return d_modelName; }

  void setTextureName(const std::string& i_textureName) { d_textureName = i_textureName; }
  const std::string& getTextureName() const { return d_textureName; }


  void setHeight(float i_height) { d_height = i_height; }
  float getHeight() const { return d_height; }

  void setSizeX(float i_sizeX) { d_sizeX = i_sizeX; }
  float getSizeX() const { return d_sizeX; }

  void setSizeZ(float i_sizeZ) { d_sizeZ = i_sizeZ; }
  float getSizeZ() const { return d_sizeZ; }

private:

  std::string d_modelName;
  std::string d_textureName;

  float d_sizeX;
  float d_sizeZ;
  float d_height;

};
