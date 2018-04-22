#pragma once


class RenderDevice;
struct Material;


class TextureLightShader
{
public:

  void load(RenderDevice& i_renderDevice);
  void unload();

  void setParameters(RenderDevice& i_renderDevice,
    XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix,
    ID3D11ShaderResourceView* texture, XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor);

  void setMaterial(const Material& i_material);

  void render(RenderDevice& i_renderDevice, int i_indicesCount);

private:

  ID3D11VertexShader* d_vertexShader;
  ID3D11PixelShader* d_pixelShader;
  ID3D11InputLayout* d_layout;
  ID3D11SamplerState* d_sampleState;
  ID3D11Buffer* d_matrixBuffer;
  ID3D11Buffer* d_lightBuffer;

};
