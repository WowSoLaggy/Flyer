#pragma once

#include "Material.h"
#include "ResourceController.h"

class IRenderable;
class ModelResource;
class RenderDevice;
using RenderFunc = std::function<void(const IRenderable& i_renderable)>;

class IRenderable
{
public:

  virtual ~IRenderable() { }

  virtual void load(RenderDevice& i_renderDevice, const ResourceController& i_resourceController) = 0;
  virtual void unload() = 0;

  virtual void render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const = 0;
  virtual void renderBuffers(RenderDevice& i_renderDevice) const { };
  virtual ID3D11ShaderResourceView* getTexture() const = 0;
  virtual int getIndexCount() const { return 0; }
  
  virtual XMMATRIX getWorldMatrix() const = 0;

  virtual MaterialSequence getMaterialSequence() const { return MaterialSequence::createBlank(); }

  virtual ResourceId getModelResourceId() const { return INVALID_RESOURCE_ID; }

};
