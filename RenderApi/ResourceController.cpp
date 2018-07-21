#include "stdafx.h"
#include "ResourceController.h"


ResourceId ResourceController::getMeshResourceId(const std::string& i_resourceName) const
{
  return d_resourceIdsMap.at(i_resourceName);
}

ResourceId ResourceController::getTextureResourceId(const std::string& i_resourceName) const
{
  return d_resourceIdsMap.at(i_resourceName);
}


const MeshResource& ResourceController::getMeshResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const MeshResource&>(*d_resourceMap.at(i_resourceId));
}

const TextureResource& ResourceController::getTextureResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const TextureResource&>(*d_resourceMap.at(i_resourceId));
}


void ResourceController::initialize()
{
}

void ResourceController::dispose()
{
}


void ResourceController::loadResources(IRenderDevice& i_renderDevice)
{
  for (auto& it : d_resourceMap)
    it.second->load(i_renderDevice);
}

void ResourceController::unloadResources()
{
  for (auto& it : d_resourceMap)
    it.second->unload();
}
