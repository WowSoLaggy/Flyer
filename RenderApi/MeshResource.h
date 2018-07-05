#pragma once

#include "Material.h"
#include "IResource.h"


class MeshResource : public IResource
{
public:

  virtual ResourceType getResourceType() const override final { return ResourceType::Mesh; }

  virtual void load() override;
  virtual void unload() override;

  ID3D11Buffer* getIndexBufferPtr() const { return d_indexBuffer; }
  ID3D11Buffer* getVertexBufferPtr() const { return d_vertexBuffer; }
  const MaterialSequence& getMaterialSequence() const { return d_materialSequence; }

private:

  ID3D11Buffer* d_indexBuffer;
  ID3D11Buffer* d_vertexBuffer;
  MaterialSequence d_materialSequence;

};
