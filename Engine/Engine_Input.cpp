#include "stdafx.h"
#include "Engine.h"

#include <LaggyDx/IInputDevice.h>


void Engine::processMessage(const Sdk::Message& i_inputMessage)
{
  d_inputDevice->processMessage(i_inputMessage);
}
