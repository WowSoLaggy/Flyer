#include "stdafx.h"
#include "IEngine.h"

#include "Engine.h"


std::shared_ptr<IEngine> IEngine::create()
{
  auto* pEngine = new Engine();
  return std::shared_ptr<IEngine>(pEngine);
}
