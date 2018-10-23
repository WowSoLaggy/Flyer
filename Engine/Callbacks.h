#pragma once

#include "EngineFwd.h"

#include <InputApi/InputDeviceFwd.h>


using ControlCallback = std::function<ControlSignal()>;
using UpdateCallback = std::function<void(double)>;
using RenderCallback = std::function<void(double)>;
using InputCallback = std::function<void(double, const KeyboardState& i_keyboardState)>;
