#pragma once

#include "IRenderable.h"


class GameObject : public IRenderable
{
public:

  XMFLOAT3 position;

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const override;
  virtual void renderBuffers(RenderDevice& i_renderDevice) const override;
  virtual ID3D11ShaderResourceView* getTexture() const override { return d_texture; }
  virtual int getIndexCount() const override { return d_indexCount; }

private:

  const std::wstring c_textureName = L"Grass.dds";

  ID3D11Buffer * d_vertexBuffer;
  ID3D11Buffer* d_indexBuffer;
  int d_indexCount;

  ID3D11ShaderResourceView* d_texture;

  void loadBuffers(RenderDevice& i_renderDevice);
  void loadTexture(RenderDevice& i_renderDevice);

  void unloadBuffers();
  void unloadTexture();

};
