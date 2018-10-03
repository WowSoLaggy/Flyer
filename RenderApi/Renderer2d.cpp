#include "stdafx.h"
#include "Renderer2d.h"

#include "IObject2d.h"
#include "FontResource.h"
#include "RenderDevice.h"
#include "ResourceController.h"


Renderer2d::Renderer2d(
  IRenderDevice& io_renderDevice,
  const IResourceController& i_resourceController)
  : d_renderDevice(io_renderDevice)
  , d_resourceController(i_resourceController)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);

  d_spriteBatch = std::make_shared<SpriteBatch>(renderDevice.getDeviceContextPtr());
}

Renderer2d::~Renderer2d()
{
  d_spriteBatch.reset();
}


void Renderer2d::beginScene()
{
  d_spriteBatch->Begin();
}

void Renderer2d::endScene()
{
  d_spriteBatch->End();
}


void Renderer2d::renderObject(const IObject2d& i_object2d)
{
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);

  const auto& fontResource = resourceController.getFontResource(i_object2d.getFontResourceId());
  fontResource.getSpriteFont()->DrawString(d_spriteBatch.get(), L"Hello, world!", XMFLOAT2(0, 0));
}
