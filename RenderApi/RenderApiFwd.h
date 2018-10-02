#pragma once

class IRenderDevice;
class ICamera;
class IObject3d;
class IRenderer3d;

using ResourceId = int;
class IResourceController;
class IResource;
class MeshResource;
class TextureResource;
class PixelShaderResource;
class VertexShaderResource;
class FontResource;

struct Material;
struct MaterialSpan;

namespace DirectX
{
  class SpriteFont;
  class SpriteBatch;
}
