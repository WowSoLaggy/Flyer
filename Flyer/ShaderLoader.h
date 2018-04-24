#pragma once

class RenderDevice;


class ShaderLoader
{
public:

  static void loadVertexShader(const std::string& i_fileName,
    RenderDevice& i_renderDevice, ID3D11VertexShader*& i_vertexShader);

  static void loadPixelShader(const std::string& i_fileName,
    RenderDevice& i_renderDevice, ID3D11PixelShader*& i_pixelShader);
};
