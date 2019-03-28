#pragma once

#include <cstdint>


struct Message
{
  uint64_t message;
  uint64_t wParam;
  int64_t lParam;
};
