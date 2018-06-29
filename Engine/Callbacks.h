#pragma once

enum class ControlSignal
{
  Run = 0,
  Stop = 1,
};

using ControlCallback = std::function<ControlSignal()>;


using UpdateCallback = std::function<void(double)>;
