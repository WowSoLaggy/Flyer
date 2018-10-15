#pragma once

class IRenderDevice;
class ICamera;
class IObject3d;
class IObject2d;
class IRenderer3d;
class IRenderer2d;

using ResourceId = int;
class IResourceController;
class IResource;
class MeshResourceObj;
class TextureResource;
class PixelShaderResource;
class VertexShaderResource;
class FontResource;

class VertexBuffer;
class IndexBuffer;

struct Material;
struct MaterialSpan;
class MaterialSequence;

struct ID3D11Buffer;

namespace DirectX
{
  class SpriteFont;
  class SpriteBatch;
}
