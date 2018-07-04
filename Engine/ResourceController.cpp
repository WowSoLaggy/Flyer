#include "stdafx.h"
#include "ResourceController.h"


ResourceDesc ResourceController::getResourceDesc() const
{
  return { (ResourceId)0, std::ref(*this) };
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
