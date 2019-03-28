#include "stdafx.h"
#include "Random.h"


namespace Random_NS
{
  void randomize()
  {
    srand((unsigned int)time(nullptr));
  }

}; // Random_NS
