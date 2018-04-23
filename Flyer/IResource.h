#pragma once


enum class ResourceType
{
  Texture,
  Model,
};


class IResource
{
public:

  virtual ResourceType getResourceType() const = 0;

  virtual void load() = 0;
  virtual void unload() = 0;

};
