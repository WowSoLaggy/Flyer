#include "stdafx.h"
#include "IRenderDevice.h"

#include "RenderDevice.h"


std::shared_ptr<IRenderDevice> IRenderDevice::create()
{
  auto* pRenderDevice = new RenderDevice();
  return std::shared_ptr<IRenderDevice>(pRenderDevice);
}
