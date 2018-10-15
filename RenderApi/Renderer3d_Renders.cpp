#include "stdafx.h"
#include "Renderer3d.h"

#include "MeshResourceObj.h"
#include "RenderDevice.h"
#include "ResourceController.h"
#include "TextureResource.h"


void Renderer3d::renderObject(
  ResourceId i_textureResourceId, ResourceId i_meshResourceObjId,
  const Vector3& i_position, const Vector3& i_rotation)
{
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);
  const auto& meshResourceObj = resourceController.getMeshResourceObj(i_meshResourceObjId);

  renderObject(i_textureResourceId,
    meshResourceObj.getVertexBuffer(), meshResourceObj.getIndexBuffer(),
    meshResourceObj.getMaterialSpans(),
    i_position, i_rotation);
}


void Renderer3d::renderObject(
  ResourceId i_textureResourceId,
  const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
  const std::vector<MaterialSpan>& i_materialSpans,
  const Vector3& i_position, const Vector3& i_rotation)
{
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);
  const auto& textureResource = resourceController.getTextureResource(i_textureResourceId);

  setBuffers(
    i_vertexBuffer.getPtr(), i_indexBuffer.getPtr(),
    unsigned int(i_vertexBuffer.getStride()));


  setShaderMatrices(i_position, i_rotation);
  setShaderTexture(textureResource.getTexturePtr());

  
  for (auto& materialSpan : i_materialSpans)
    drawMaterial(materialSpan);
}
