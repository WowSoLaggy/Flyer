#pragma once

#include "IRenderable.h"
#include "ResourceController.h"

class ModelResource;


class GameObject : public IRenderable
{
public:

  void setResourceNames(const std::string& i_modelName, const std::string& i_textureName);
  void setPosition(XMFLOAT3 i_position);

  virtual void load(RenderDevice& i_renderDevice, const ResourceController& i_resourceController) override;
  virtual void unload() override;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const override;
  virtual ResourceId getModelResourceId() const override;
  virtual ID3D11ShaderResourceView* getTexture() const override { return d_texture; }

  virtual XMMATRIX getWorldMatrix() const override { return d_worldMatrix; }

private:

  std::string d_modelName;
  std::string d_textureName;

  ResourceId d_modelResourceId;

  ID3D11ShaderResourceView* d_texture;

  XMFLOAT3 d_position;
  XMMATRIX d_worldMatrix;
  void updateWorldMatrix();

  void loadTexture(RenderDevice& i_renderDevice);
  void unloadTexture();

};
