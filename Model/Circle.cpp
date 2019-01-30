#include "stdafx.h"
#include "Circle.h"


Circle::Circle(double i_radius)
{
  setRadius(i_radius);
}


void Circle::setRadius(double i_radius)
{
  d_radius = i_radius;
  d_radiusSq = i_radius * i_radius;
}
