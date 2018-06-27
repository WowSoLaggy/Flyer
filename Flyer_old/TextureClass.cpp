#include "stdafx.h"
#include "TextureClass.h"


TextureClass::TextureClass()
{
  d_texture = 0;
}


bool TextureClass::Initialize(ID3D11Device* device, const std::wstring& filename)
{
  // Load the texture in.
  HRESULT result = CreateDDSTextureFromFile(device, filename.c_str(), nullptr, &d_texture);
  if (FAILED(result))
    return false;

  return true;
}

void TextureClass::Shutdown()
{
  // Release the texture resource.
  if (d_texture)
  {
    d_texture->Release();
    d_texture = 0;
  }

  return;
}

ID3D11ShaderResourceView* TextureClass::GetTexture()
{
  return d_texture;
}
