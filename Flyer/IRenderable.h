#pragma once

class RenderDevice;
class IRenderable;
using RenderFunc = std::function<void(const IRenderable& i_renderable)>;

class IRenderable
{
public:

  virtual void load(RenderDevice& i_renderDevice) = 0;
  virtual void unload() = 0;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const = 0;
  virtual void renderBuffers(RenderDevice& i_renderDevice) const = 0;
  virtual ID3D11ShaderResourceView* getTexture() const = 0;
  virtual int getIndexCount() const = 0;
  
  virtual XMMATRIX getWorldMatrix() const = 0;

};
