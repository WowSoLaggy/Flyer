#pragma once

#include "IRenderer2d.h"
#include "RenderApiFwd.h"


class Renderer2d: public IRenderer2d
{
public:

  Renderer2d(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController);
  ~Renderer2d();

  virtual void beginScene() override;
  virtual void endScene() override;

  virtual void renderText(const std::string& i_text, ResourceId i_fontResourceId, const Vector2& i_position) override;
  virtual void renderTexture(ResourceId i_textureResourceId, const Vector2& i_position) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;

  std::shared_ptr<SpriteBatch> d_spriteBatch;

};
