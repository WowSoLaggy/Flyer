#include "stdafx.h"
#include "MeshResource.h"

#include "MeshLoader.h"


MeshResource::MeshResource(const std::string& i_meshFilePath)
  : d_meshFilePath(i_meshFilePath)
{
}


void MeshResource::load(IRenderDevice& i_renderDevice)
{
  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  MeshLoader::loadInfoFromObjFile(d_meshFilePath, vertices, indices, d_materialSequence);

  d_vertexBuffer.create(i_renderDevice, vertices);
  d_indexBuffer.create(i_renderDevice, indices);
}

void MeshResource::unload()
{
  d_vertexBuffer.dispose();
  d_indexBuffer.dispose();
}
