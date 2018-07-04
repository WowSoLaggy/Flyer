#include "stdafx.h"
#include "Resource.h"


Resource::Resource(ResourceId i_resourceId)
  : d_resourceId(i_resourceId) 
{
}

ResourceId Resource::getResourceId() const
{
  return d_resourceId;
}
