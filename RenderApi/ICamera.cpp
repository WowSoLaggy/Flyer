#include "stdafx.h"
#include "ICamera.h"

#include "Camera.h"


std::shared_ptr<ICamera> ICamera::createCamera(float i_viewportAspect)
{
  auto* pCamera = new Camera(i_viewportAspect);
  return std::shared_ptr<ICamera>(pCamera);
}
