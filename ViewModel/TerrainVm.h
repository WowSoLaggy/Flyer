#pragma once

#include <Model/ModelFwd.h>
#include <RenderApi/IObject3d.h>
#include <RenderApi/RenderApiFwd.h>


class TerrainVm: public IObject3d
{
public:

  TerrainVm(const IResourceController& i_resourceController, const Terrain& i_terrain);

  virtual ResourceId getMeshResourceId() const override { return d_meshResourceId; }
  virtual ResourceId getTextureResourceId() const override { return d_textureResourceId; }

  virtual Vector3 getPosition() const override;

private:

  const Terrain& d_terrain;

  const ResourceId d_meshResourceId;
  const ResourceId d_textureResourceId;
};
