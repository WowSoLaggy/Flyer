#pragma once

#include "IRenderable.h"


class GameObject : public IRenderable
{
public:

  void setResourceNames(const std::wstring& i_modelName, const std::wstring& i_textureName);
  void setPosition(XMFLOAT3 i_position);

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const override;
  virtual void renderBuffers(RenderDevice& i_renderDevice) const override;
  virtual ID3D11ShaderResourceView* getTexture() const override { return d_texture; }
  virtual int getIndexCount() const override { return d_indexCount; }

  virtual XMMATRIX getWorldMatrix() const override { return d_worldMatrix; }

  virtual MaterialSequence getMaterialSequence() const override { return d_materialSequence; }

private:

  std::wstring d_modelName;
  std::wstring d_textureName;

  ID3D11Buffer* d_vertexBuffer;
  ID3D11Buffer* d_indexBuffer;
  MaterialSequence d_materialSequence;
  int d_indexCount;

  ID3D11ShaderResourceView* d_texture;

  XMFLOAT3 d_position;
  XMMATRIX d_worldMatrix;
  void updateWorldMatrix();

  void loadBuffers(RenderDevice& i_renderDevice);
  void loadTexture(RenderDevice& i_renderDevice);

  void unloadBuffers();
  void unloadTexture();

};
