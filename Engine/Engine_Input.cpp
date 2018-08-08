#include "stdafx.h"
#include "Engine.h"

#include <InputApi/IInputDevice.h>


void Engine::processMessage(const InputMessage& i_inputMessage)
{
  d_inputDevice->processMessage(i_inputMessage);
}
