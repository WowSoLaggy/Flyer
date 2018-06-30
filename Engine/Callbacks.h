#pragma once

#include "EngineFwd.h"


using ControlCallback = std::function<ControlSignal()>;
using UpdateCallback = std::function<void(double)>;
