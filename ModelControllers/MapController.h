#pragma once

#include <Model/ModelFwd.h>

class MapController final
{
public:

  static MapController createNewMap();

public:

  void update(double i_dt);

private:

  MapController();

  std::unique_ptr<Map> d_map;

};
