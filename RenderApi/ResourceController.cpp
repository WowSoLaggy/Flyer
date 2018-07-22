#include "stdafx.h"
#include "ResourceController.h"

#include "MeshResource.h"
#include "TextureResource.h"
#include "VertexShaderResource.h"


namespace
{

  bool isDirNotDots(struct dirent* pEntity)
  {
    return pEntity && (pEntity->d_type == DT_DIR) &&
      (strcmp(pEntity->d_name, ".") != 0) && (strcmp(pEntity->d_name, "..") != 0);
  }

} // anon NS


ResourceId ResourceController::getResourceId(const std::string& i_resourceName) const
{
  return d_nameToIdMap.at(i_resourceName);
}


const MeshResource& ResourceController::getMeshResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const MeshResource&>(*d_idToResourceMap.at(i_resourceId));
}

const TextureResource& ResourceController::getTextureResource(ResourceId i_resourceId) const
{
  return dynamic_cast<const TextureResource&>(*d_idToResourceMap.at(i_resourceId));
}


void ResourceController::initialize(const std::string& i_resourcesFolder)
{
  indexResourcesInDir(i_resourcesFolder);
}

void ResourceController::dispose()
{
  clearResoures();
}


void ResourceController::loadResources(IRenderDevice& i_renderDevice)
{
  for (auto& it : d_idToResourceMap)
    it.second->load(i_renderDevice);
}

void ResourceController::unloadResources()
{
  for (auto& it : d_idToResourceMap)
    it.second->unload();
}


ResourceId ResourceController::getFreeResourceId()
{
  return d_nextResourceId++;
}


void ResourceController::indexResourcesInDir(const std::string& i_dirName)
{
  auto* pDir = opendir(i_dirName.c_str());
  if (!pDir)
    return;

  struct dirent* pEntity;
  while (pEntity = readdir(pDir))
  {
    if (isDirNotDots(pEntity))
    {
      indexResourcesInDir(i_dirName + pEntity->d_name + "\\");
      continue;
    }

    if (pEntity->d_type != DT_REG)
    {
      // Not a regular file - we don't care
      continue;
    }

    const std::regex texturePattern("\\w*.(dds)");
    const std::regex modelPattern("\\w*.(obj)");
    const std::regex vertexShaderPattern("\\w*.(vs)");
    const std::regex pixelShaderPattern("\\w*.(ps)");

    auto resourceName = i_dirName + pEntity->d_name;
    auto freeResourceId = getFreeResourceId();

    if (std::regex_match(pEntity->d_name, modelPattern))
    {
      d_nameToIdMap.insert({ resourceName, freeResourceId });
      d_idToResourceMap.insert({ freeResourceId, std::make_shared<MeshResource>(resourceName) });
    }
    else if (std::regex_match(pEntity->d_name, texturePattern))
    {
      d_nameToIdMap.insert({ resourceName, freeResourceId });
      d_idToResourceMap.insert({ freeResourceId, std::make_shared<TextureResource>(resourceName) });
    }
    else if (std::regex_match(pEntity->d_name, vertexShaderPattern))
    {
      d_nameToIdMap.insert({ resourceName, freeResourceId });
      d_idToResourceMap.insert({ freeResourceId, std::make_shared<VertexShaderResource>(resourceName) });
    }
  }
}

void ResourceController::clearResoures()
{
  d_nameToIdMap.clear();
  d_idToResourceMap.clear();
}
