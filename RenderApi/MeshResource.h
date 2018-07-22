#pragma once

#include "IResource.h"
#include "IndexBuffer.h"
#include "MaterialSequence.h"
#include "VertexBuffer.h"


class MeshResource : public IResource
{
public:

  MeshResource(const std::string& i_meshFilePath);

  virtual void load(IRenderDevice& i_renderDevice) override;
  virtual void unload() override;

  const IndexBuffer& getIndexBuffer() const { return d_indexBuffer; }
  const VertexBuffer& getVertexBuffer() const { return d_vertexBuffer; }
  const std::vector<MaterialSpan>& getMaterialSpans() const { return d_materialSequence.getMaterialSpans(); }

private:

  const std::string d_meshFilePath;

  IndexBuffer d_indexBuffer;
  VertexBuffer d_vertexBuffer;
  MaterialSequence d_materialSequence;

};
