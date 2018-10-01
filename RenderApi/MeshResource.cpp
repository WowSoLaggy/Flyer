#include "stdafx.h"
#include "MeshResource.h"

#include "MeshLoader.h"


MeshResource::MeshResource(std::string i_meshFilePath)
  : d_meshFilePath(std::move(i_meshFilePath))
{
}


void MeshResource::load(IRenderDevice& i_renderDevice)
{
  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  MeshLoader::loadInfoFromObjFile(d_meshFilePath, vertices, indices, d_materialSequence);

  d_vertexBuffer.create(i_renderDevice, vertices);
  d_indexBuffer.create(i_renderDevice, indices);

  if (d_materialSequence.getMaterialSpans().empty())
    d_materialSequence.add({ Material::getDefault(), 0, d_indexBuffer.getIndexCount() });
}

void MeshResource::unload()
{
  d_vertexBuffer.dispose();
  d_indexBuffer.dispose();
}
