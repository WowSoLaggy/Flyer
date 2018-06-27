#pragma once

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:

  struct VertexType
  {
    XMFLOAT3 position;
    XMFLOAT2 texture;
    XMFLOAT3 normal;
  };

public:
  ModelClass();

  bool Initialize(ID3D11Device*, const std::wstring& i_filename);
  void Shutdown();
  void Render(ID3D11DeviceContext*);

  int GetIndexCount();

  ID3D11ShaderResourceView* GetTexture();

private:
  bool InitializeBuffers(ID3D11Device*);
  void ShutdownBuffers();
  void RenderBuffers(ID3D11DeviceContext*);

  bool LoadTexture(ID3D11Device*, const std::wstring&);
  void ReleaseTexture();

private:
  ID3D11Buffer* d_vertexBuffer;
  ID3D11Buffer* d_indexBuffer;
  int d_vertexCount;
  int d_indexCount;

  TextureClass* d_Texture;
};
