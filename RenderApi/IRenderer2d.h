#pragma once

#include "RenderApiFwd.h"

#include <Sdk/SdkFwd.h>


class IRenderer2d
{
public:

  static std::shared_ptr<IRenderer2d> create(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController);

public:

  virtual ~IRenderer2d() = default;

  virtual void beginScene() = 0;
  virtual void endScene() = 0;

  virtual void renderText(const std::string& i_text, ResourceId i_fontResourceId, const Vector2& i_position) = 0;
  virtual void renderTexture(ResourceId i_textureResourceId, const Vector2& i_position) = 0;
};
