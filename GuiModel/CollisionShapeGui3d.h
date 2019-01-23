#pragma once

#include "IGui3d.h"

#include <Sdk/IModelName.h>
#include <Sdk/ITextureName.h>


class CollisionShapeGui3d : public IGui3d, public IModelName, public ITextureName
{
};
