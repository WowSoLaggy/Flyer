#pragma once

#include "IRenderer3d.h"
#include "RenderApiFwd.h"


class Renderer3d: public IRenderer3d
{
public:

  Renderer3d(
    IRenderDevice& io_renderDevice,
    const IResourceController& i_resourceController,
    const ICamera& i_camera);
  ~Renderer3d();

  virtual void beginScene() override;
  virtual void endScene() override;

  virtual void renderObject(
    ResourceId i_textureResourceId, ResourceId i_meshResourceId,
    const Vector3& i_position) override;

  virtual void renderObject(
    ResourceId i_textureResourceId,
    const VertexBuffer& i_vertexBuffer, const IndexBuffer& i_indexBuffer,
    const std::vector<MaterialSpan>& i_materialSpans, const Vector3& i_position) override;

private:

  IRenderDevice& d_renderDevice;
  const IResourceController& d_resourceController;
  const ICamera& d_camera;

  ID3D11Buffer* d_matrixBuffer;
  ID3D11Buffer* d_lightBuffer;

  void createBuffers();
  void disposeBuffers();

  void setBuffers(ID3D11Buffer* i_vertexBufferPtr, ID3D11Buffer* i_indexBufferPtr, unsigned int i_stride);
  void setShaders();
  void setShaderMatrices(const Vector3& i_position);
  void setShaderTexture(ID3D11ShaderResourceView* i_texture);
  void setShaderMaterial(const Material& i_material);
  void drawMaterial(const MaterialSpan& i_materialSpan);

};
