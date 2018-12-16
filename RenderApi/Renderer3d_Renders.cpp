#include "stdafx.h"
#include "Renderer3d.h"

#include "AnimationController.h"
#include "Camera.h"
#include "IndexBuffer.h"
#include "MaterialSequence.h"
#include "MeshResourceCmo.h"
#include "RenderDevice.h"
#include "ResourceController.h"
#include "TextureResource.h"
#include "VertexBuffer.h"


void Renderer3d::renderObject(
  ResourceId i_textureResourceId,
  const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
  const std::vector<MaterialSpan>& i_materialSpans,
  const Vector3& i_position /* = Vector3::zero() */, const Vector3& i_rotation /* = Vector3::zero() */)
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


void Renderer3d::renderObject(ResourceId i_meshResourceCmoId,
  const IAnimationController& i_animationController,
  const Vector3& i_position /* = Vector3::zero() */, const Vector3& i_rotation /* = Vector3::zero() */)
{
  auto& renderDevice = dynamic_cast<RenderDevice&>(d_renderDevice);
  const auto& resourceController = dynamic_cast<const ResourceController&>(d_resourceController);
  auto& meshResourceCmo = resourceController.getMeshResourceCmo(i_meshResourceCmoId);

  auto& camera = dynamic_cast<const Camera&>(d_camera);

  const auto& animationController = dynamic_cast<const AnimationController&>(i_animationController);
  const auto animationTransform = animationController.getTransform();

  auto worldMatrix =
    animationTransform *
    XMMatrixRotationRollPitchYaw(i_rotation.x, i_rotation.y, i_rotation.z) *
    XMMatrixTranslation(i_position.x, i_position.y, i_position.z);

  meshResourceCmo.getModel().UpdateEffects([&](IEffect* io_pEffect)
  {
    if (auto* pLights = dynamic_cast<IEffectLights*>(io_pEffect))
    {
      pLights->SetLightDirection(0, { 1.0f, -1.0f, -1.0f });
      pLights->SetAmbientLightColor({ 0.3f, 0.3f, 0.3f });
    }
  });

  CommonStates states(renderDevice.getDevicePtr());
  meshResourceCmo.getModel().Draw(renderDevice.getDeviceContextPtr(), states,
    worldMatrix, camera.getViewMatrix(), camera.getProjectionMatrix());
}
