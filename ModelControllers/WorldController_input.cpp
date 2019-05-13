#include "stdafx.h"
#include "WorldController.h"

#include "CreatureController.h"

#include <LaggyDx/KeyboardState.h>
#include <Model/ActionMoveTo.h>
#include <Model/Creature.h>


void WorldController::processInput(const Dx::KeyboardState& i_keyboardState)
{
  if (!d_player)
    return;

  Sdk::Vector3 direction = Sdk::Vector3::zero();
  const float DirectionValue = 0.1f;

  if (i_keyboardState.currentState.W)
    direction.z -= DirectionValue;
  if (i_keyboardState.currentState.S)
    direction.z += DirectionValue;

  if (i_keyboardState.currentState.A)
    direction.x -= DirectionValue;
  if (i_keyboardState.currentState.D)
    direction.x += DirectionValue;

  if (length(direction) > 0.01f)
  {
    auto goal = d_player->getPosition() + direction;

    CreatureController::setCreatureAction(d_player,
                      std::make_shared<ActionMoveTo>(xyz2xz(goal), 0.09f),
                      *this);
  }
  else
    d_player->resetMovementDirection();
}
