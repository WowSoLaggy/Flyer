#include "stdafx.h"
#include "ResourceController.h"


ResourceId ResourceController::getModelResourceId() const
{
  return (ResourceId)0;
}

ResourceId ResourceController::getTextureResourceId() const
{
  return (ResourceId)0;
}


const ModelResource& ResourceController::getModelResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const ModelResource&>(*d_resources.at(i_resourceId));
}

const TextureResource& ResourceController::getTextureResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const TextureResource&>(*d_resources.at(i_resourceId));
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
