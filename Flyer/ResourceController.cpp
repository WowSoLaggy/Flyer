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
  const std::string resourcesDirName = ".\\data\\";
  indexResources(resourcesDirName);
}

void ResourceController::clearIndices()
{
  d_resources.clear();
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
    const std::regex shaderPattern("\\w*.(cso)");

    if (std::regex_match(pEntity->d_name, texturePattern))
      d_resources.push_back(std::make_shared<TextureResource>(i_dirName + pEntity->d_name));
    else if (std::regex_match(pEntity->d_name, modelPattern))
      d_resources.push_back(std::make_shared<ModelResource>(i_dirName + pEntity->d_name));
    else if (std::regex_match(pEntity->d_name, shaderPattern))
      d_resources.push_back(std::make_shared<ShaderResource>(i_dirName + pEntity->d_name));
  }
}


void ResourceController::loadResources(RenderDevice& i_renderDevice)
{
  for (auto& resource : d_resources)
    resource->load(i_renderDevice);
}

void ResourceController::unloadResources()
{
  for (auto& resource : d_resources)
    resource->unload();
}
