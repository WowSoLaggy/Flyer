#pragma once

enum class ControlSignal
{
  Run = 0,
  Stop = 1,
};

class IEngine;

using ResourceId = int;
struct ResourceDesc;
class IResourceController;
