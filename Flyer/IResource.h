#pragma once

class RenderDevice;


enum class ResourceType
{
  Texture,
  Model,
  Shader,
};


class IResource
{
public:

  virtual ResourceType getResourceType() const = 0;

  virtual void load(RenderDevice& i_renderDevice) = 0;
  virtual void unload() = 0;

};
