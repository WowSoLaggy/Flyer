#include "stdafx.h"
#include "IResourceController.h"

#include "ResourceController.h"


std::shared_ptr<IResourceController> IResourceController::create()
{
  auto* pResourceController = new ResourceController();
  return std::shared_ptr<IResourceController>(pResourceController);
}