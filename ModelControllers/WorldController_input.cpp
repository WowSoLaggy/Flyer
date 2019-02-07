#include "stdafx.h"
#include "WorldController.h"

#include <InputApi/KeyboardState.h>
#include <Model/Creature.h>


void WorldController::processInput(const KeyboardState& i_keyboardState)
{
  if (!d_player)
    return;

  Vector3 direction = Vector3::zero();

  if (i_keyboardState.currentState.W)
    direction.z -= 1.0f;
  if (i_keyboardState.currentState.S)
    direction.z += 1.0f;

  if (i_keyboardState.currentState.A)
    direction.x -= 1.0f;
  if (i_keyboardState.currentState.D)
    direction.x += 1.0f;

  if (length(direction) > 0.01f)
  {
    d_player->setMovementDirection(direction);
    d_player->setRotation({ 0, -std::atan2(direction.z, direction.x), 0 });
  }
  else
    d_player->resetMovementDirection();
}
