#pragma once

#include <Model/World.h>
#include <Sdk/EventHandler.h>


class WorldWrapper : public World, public EventHandler
{
};
