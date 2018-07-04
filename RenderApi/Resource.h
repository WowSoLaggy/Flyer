#pragma once

#include "IResource.h"


class Resource : public IResource
{
public:

  Resource(ResourceId i_resourceId);
  virtual ~Resource() = default;

  virtual ResourceId getResourceId() const final;

private:

  ResourceId d_resourceId;

};
