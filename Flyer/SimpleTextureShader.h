#pragma once


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureShaderClass
////////////////////////////////////////////////////////////////////////////////
class SimpleTextureShader
{
private:
  struct MatrixBufferType
  {
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
  };

public:
  SimpleTextureShader();

  bool Initialize(ID3D11Device*, HWND);
  void Shutdown();
  bool Render(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);

private:
  bool InitializeShader(ID3D11Device*, HWND);
  void ShutdownShader();

  bool SetShaderParameters(ID3D11DeviceContext*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
  void RenderShader(ID3D11DeviceContext*, int);

private:
  ID3D11VertexShader* d_vertexShader;
  ID3D11PixelShader* d_pixelShader;
  ID3D11InputLayout* d_layout;
  ID3D11Buffer* d_matrixBuffer;

  ID3D11SamplerState* d_sampleState;
};
