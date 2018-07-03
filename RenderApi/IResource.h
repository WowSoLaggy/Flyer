#pragma once


enum class ResourceType
{
  Texture,
  Model,
  Shader,
};


class IResource
{
public:

  virtual ~IResource() = default;

  virtual ResourceType getResourceType() const = 0;

  virtual void load() = 0;
  virtual void unload() = 0;

};
