#include "stdafx.h"
#include "ICamera.h"

#include "Camera.h"


std::shared_ptr<ICamera> ICamera::createCamera(int i_screenWidth, int i_screenHeight)
{
  auto* pCamera = new Camera(i_screenWidth, i_screenHeight);
  return std::shared_ptr<ICamera>(pCamera);
}
