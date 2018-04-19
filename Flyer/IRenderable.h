#pragma once


class RenderDevice;


class IRenderable
{
public:

  virtual void load(RenderDevice& i_renderDevice) = 0;
  virtual void unload() = 0;

  virtual void render(RenderDevice& i_renderDevice) const = 0;
  virtual ID3D11ShaderResourceView* getTexture() const = 0;
  virtual int getIndexCount() const = 0;

};
