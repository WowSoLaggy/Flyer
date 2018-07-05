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


void ResourceController::loadResources()
{
}

void ResourceController::unloadResources()
{
}
