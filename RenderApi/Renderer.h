#pragma once

#include "IRenderer.h"
#include "RenderApiFwd.h"

#include <Sdk/SdkFwd.h>


class Renderer : public IRenderer
{
public:

  Renderer(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);
  ~Renderer();

  virtual void renderObject(const IObject3D& i_object) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  const ICamera& d_camera;

  ResourceId d_pixelShaderResourceId;
  ResourceId d_vertexShaderResourceId;

  ID3D11Buffer* d_matrixBuffer;
  ID3D11Buffer* d_lightBuffer;

  void createBuffers();
  void disposeBuffers();

  void setBuffers(ID3D11Buffer* i_vertexBufferPtr, ID3D11Buffer* i_indexBufferPtr, unsigned int i_stride);
  void setShaderMatrices(const Vector3& i_position);
  void setShaderTexture(ID3D11ShaderResourceView* i_texture);
  void setShaderMaterial(const Material& i_material);

};
