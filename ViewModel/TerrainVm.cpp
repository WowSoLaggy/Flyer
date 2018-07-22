#include "stdafx.h"
#include "TerrainVm.h"

#include <Model/Terrain.h>
#include <RenderApi/IResourceController.h>


TerrainVm::TerrainVm(const IResourceController& i_resourceController, const Terrain& i_terrain)
  : d_terrain(i_terrain)
  , d_meshResourceId(i_resourceController.getResourceId(d_terrain.getModelName()))
  , d_textureResourceId(i_resourceController.getResourceId(d_terrain.getTextureName()))
{
}


Vector3 TerrainVm::getPosition() const
{
  return { 0, 0, 0 };
}
