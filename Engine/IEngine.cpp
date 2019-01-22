#include "stdafx.h"
#include "IEngine.h"

#include "Engine.h"


std::shared_ptr<IEngine> IEngine::create()
{
  return std::make_shared<Engine>();
}
