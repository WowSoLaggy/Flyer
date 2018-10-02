#pragma once

#include "IRenderer3d.h"
#include "RenderApiFwd.h"

#include <Sdk/SdkFwd.h>


class Renderer3d: public IRenderer3d
{
public:

  Renderer3d(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);
  ~Renderer3d();

  virtual void renderObject(const IObject3d& i_object3d) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  const ICamera& d_camera;

  ID3D11Buffer* d_matrixBuffer;
  ID3D11Buffer* d_lightBuffer;

  void createBuffers();
  void disposeBuffers();

  void setBuffers(ID3D11Buffer* i_vertexBufferPtr, ID3D11Buffer* i_indexBufferPtr, unsigned int i_stride);
  void setShaders(
    const VertexShaderResource& i_vertexShaderResource,
    const PixelShaderResource& i_pixelShaderResource,
    ID3D11SamplerState* i_samplerState);
  void setShaderMatrices(const Vector3& i_position);
  void setShaderTexture(ID3D11ShaderResourceView* i_texture);
  void setShaderMaterial(const Material& i_material);
  void drawMaterial(const MaterialSpan& i_materialSpan);

};
