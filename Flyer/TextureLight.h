#pragma once


////////////////////////////////////////////////////////////////////////////////
// Class name: LightShaderClass
////////////////////////////////////////////////////////////////////////////////
class LightShaderClass
{
private:
  struct MatrixBufferType
  {
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
  };

  struct LightBufferType
  {
    XMFLOAT4 diffuseColor;
    XMFLOAT3 lightDirection;
    float padding;  // Added extra padding so structure is a multiple of 16 for CreateBuffer function requirements.
  };

public:
  LightShaderClass();

  bool Initialize(ID3D11Device*, HWND);
  void Shutdown();
  bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX,
    ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

private:
  bool InitializeShader(ID3D11Device*, HWND);
  void ShutdownShader();

  bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX,
    ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);
  void RenderShader(ID3D11DeviceContext*, int);

private:
  ID3D11VertexShader* d_vertexShader;
  ID3D11PixelShader* d_pixelShader;
  ID3D11InputLayout* d_layout;
  ID3D11SamplerState* d_sampleState;
  ID3D11Buffer* d_matrixBuffer;
  ID3D11Buffer* d_lightBuffer;

};
