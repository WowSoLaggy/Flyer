#pragma once

#include "IHud.h"

#include <Sdk/IModelName.h>
#include <Sdk/ITextureName.h>


class CollisionShapeHud : public IHud, public IModelName, public ITextureName
{
};
