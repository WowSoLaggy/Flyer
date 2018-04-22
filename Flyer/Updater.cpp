#include "stdafx.h"
#include "Updater.h"

#include "Map.h"


void Updater::update(double i_dt, const Map& i_map)
{
  if (i_map.d_objects.empty())
    return;

  static double x = 0;
  x += i_dt;

  auto& player = const_cast<GameObject&>(i_map.d_objects.front());
  player.setPosition({
    (float)(std::sin(x) * 5),
    (float)(std::cos(x) * 5),
    0 });
}
