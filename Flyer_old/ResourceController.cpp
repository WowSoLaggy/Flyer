#include "stdafx.h"
#include "ResourceController.h"

#include "dirent.h"
#include "ModelResource.h"
#include "TextureResource.h"
#include "ShaderResource.h"
#include "Utils.h"


namespace
{

  bool isDirNotDots(struct dirent* pEntity)
  {
    return pEntity && (pEntity->d_type == DT_DIR) &&
      (strcmp(pEntity->d_name, ".") != 0) && (strcmp(pEntity->d_name, "..") != 0);
  }

} // anon NS


void ResourceController::indexResources()
{
  clearIndices();

  const std::string resourcesDirName = ".\\data\\";
  indexResources(resourcesDirName);
}

void ResourceController::clearIndices()
{
  d_resources.clear();
  d_nextResourceId = 0;
}


ResourceId ResourceController::getFreeResourceId()
{
  return d_nextResourceId++;
}


void ResourceController::indexResources(const std::string& i_dirName)
{
  auto* pDir = opendir(i_dirName.c_str());
  if (!pDir)
    return;

  struct dirent* pEntity;
  while (pEntity = readdir(pDir))
  {
    if (isDirNotDots(pEntity))
    {
      indexResources(i_dirName + pEntity->d_name + "\\");
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

    if (std::regex_match(pEntity->d_name, texturePattern))
    {
      d_resources.insert({ getFreeResourceId(),
        std::make_shared<TextureResource>(i_dirName + pEntity->d_name) });
    }
    else if (std::regex_match(pEntity->d_name, modelPattern))
    {
      d_resources.insert({ getFreeResourceId(),
        std::make_shared<ModelResource>(i_dirName + pEntity->d_name) });
    }
    else if (std::regex_match(pEntity->d_name, vertexShaderPattern))
    {
      d_resources.insert({ getFreeResourceId(),
        std::make_shared<ShaderResource>(i_dirName + pEntity->d_name, ShaderType::Vertex) });
    }
    else if (std::regex_match(pEntity->d_name, pixelShaderPattern))
    {
      d_resources.insert({ getFreeResourceId(),
        std::make_shared<ShaderResource>(i_dirName + pEntity->d_name, ShaderType::Pixel) });
    }
  }
}


void ResourceController::loadResources(RenderDevice& i_renderDevice)
{
  std::for_each(d_resources.begin(), d_resources.end(),
    [&](auto& pair) { pair.second->load(i_renderDevice); });
}

void ResourceController::unloadResources()
{
  std::for_each(d_resources.begin(), d_resources.end(),
    [&](auto& pair) { pair.second->unload(); });
}


ResourceId ResourceController::getResourceId(const std::string& i_resourceName) const
{
  auto it = std::find_if(d_resources.begin(), d_resources.end(),
    [&](auto& pair) { return pair.second->getResourceName() == i_resourceName; });
  if (it == d_resources.end())
    return INVALID_RESOURCE_ID;

  return it->first;
}

std::shared_ptr<IResource> ResourceController::getResource(ResourceId i_resourceId)
{
  auto it = d_resources.find(i_resourceId);
  if (it == d_resources.end())
    return nullptr;
  return it->second;
}
