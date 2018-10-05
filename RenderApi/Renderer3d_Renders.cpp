#include "stdafx.h"
#include "Renderer3d.h"

#include "MeshResource.h"
#include "RenderDevice.h"
#include "ResourceController.h"
#include "TextureResource.h"


void Renderer3d::renderObject(
  ResourceId i_textureResourceId, ResourceId i_meshResourceId,
  const Vector3& i_position)
{
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);
  const auto& meshResource = resourceController.getMeshResource(i_meshResourceId);

  renderObject(i_textureResourceId,
    meshResource.getVertexBuffer(), meshResource.getIndexBuffer(),
    meshResource.getMaterialSpans(), i_position);
}


void Renderer3d::renderObject(
  ResourceId i_textureResourceId,
  const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
  const std::vector<MaterialSpan>& i_materialSpans, const Vector3& i_position)
{
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);
  const auto& textureResource = resourceController.getTextureResource(i_textureResourceId);

  setBuffers(
    i_vertexBuffer.getPtr(), i_indexBuffer.getPtr(),
    unsigned int(i_vertexBuffer.getStride()));


  setShaderMatrices(i_position);
  setShaderTexture(textureResource.getTexturePtr());

  
  for (auto& materialSpan : i_materialSpans)
    drawMaterial(materialSpan);
}
