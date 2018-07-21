#pragma once

#include "RenderApiFwd.h"
#include "VertexTypes.h"


class VertexBuffer
{
public:

  int getVerticeCount() const { return d_verticeCount; }
  ID3D11Buffer* getPtr() const { return d_vertexBuffer; }

  void create(IRenderDevice& i_renderDevice, const std::vector<VertexTypePosTexNorm>& i_vertices);
  void dispose();

private:

  int d_verticeCount;
  ID3D11Buffer* d_vertexBuffer;

};
