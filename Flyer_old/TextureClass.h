#pragma once


////////////////////////////////////////////////////////////////////////////////
// Class name: TextureClass
////////////////////////////////////////////////////////////////////////////////
class TextureClass
{
public:
  TextureClass();

  bool Initialize(ID3D11Device*, const std::wstring&);
  void Shutdown();

  ID3D11ShaderResourceView* GetTexture();

private:
  ID3D11ShaderResourceView* d_texture;
};
