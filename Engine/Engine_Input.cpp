#include "stdafx.h"
#include "Engine.h"

#include <InputApi/IInputDevice.h>


void Engine::processMessage(const Message& i_inputMessage)
{
  d_inputDevice->processMessage(i_inputMessage);
}
