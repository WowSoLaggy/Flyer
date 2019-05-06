#pragma once

#include "IGui3d.h"

#include <LaggySdk/IModelName.h>
#include <LaggySdk/ITextureName.h>


class CollisionShapeGui3d : public IGui3d, public Sdk::IModelName, public Sdk::ITextureName
{
};
