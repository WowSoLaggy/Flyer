#include "stdafx.h"
#include "ResourceController.h"

#include "dirent.h"
#include "ModelResource.h"
#include "TextureResource.h"
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
  const std::string resourcesDirName = ".\\";
  indexResources(resourcesDirName);
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

    std::regex texturePattern("\\w*.(dds)");
    std::regex modelPattern("\\w*.(obj)");

    if (std::regex_match(pEntity->d_name, texturePattern))
      d_resources.push_back(std::make_shared<TextureResource>(i_dirName + pEntity->d_name));
    else if (std::regex_match(pEntity->d_name, modelPattern))
      d_resources.push_back(std::make_shared<ModelResource>(i_dirName + pEntity->d_name));
  }
}
