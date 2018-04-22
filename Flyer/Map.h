#pragma once

#include "GameObject.h"
#include "IRenderable.h"


class Map : public IRenderable
{
public:

  std::vector<GameObject> d_objects;

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const override;
  virtual void renderBuffers(RenderDevice& i_renderDevice) const override;
  virtual ID3D11ShaderResourceView* getTexture() const override { return d_texture; }
  virtual int getIndexCount() const override { return d_indexCount; }

  virtual XMMATRIX getWorldMatrix() const override { return d_worldMatrix; }

  virtual MaterialSequence getMaterialSequence() const override { return d_materialSequence; }

private:

  const int c_width = 20;
  const int c_height = 20;
  const float c_defaultTerrainHeight = 0.0f;
  const std::wstring c_textureName = L"Grass.dds";

  ID3D11Buffer* d_vertexBuffer;
  ID3D11Buffer* d_indexBuffer;
  MaterialSequence d_materialSequence;
  int d_indexCount;

  ID3D11ShaderResourceView* d_texture;

  XMMATRIX d_worldMatrix;

  void loadBuffers(RenderDevice& i_renderDevice);
  void loadTexture(RenderDevice& i_renderDevice);

  void unloadBuffers();
  void unloadTexture();

};
