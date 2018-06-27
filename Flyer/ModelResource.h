#pragma once

#include "IResource.h"
#include "Material.h"


class ModelResource : public IResource
{
public:

  ModelResource(const std::string& i_modelName);

  virtual ResourceType getResourceType() const override { return ResourceType::Model; }
  virtual const std::string& getResourceName() const override { return d_modelName; }

  virtual void load(RenderDevice& i_renderDevice) override;
  virtual void unload() override;

  int getIndicesCount() { return d_indexCount; }
  void setBuffersToRender(RenderDevice& i_renderDevice) const;

private:

  const std::string d_modelName;

  ID3D11Buffer* d_vertexBuffer;
  ID3D11Buffer* d_indexBuffer;
  MaterialSequence d_materialSequence;
  int d_indexCount;

};
