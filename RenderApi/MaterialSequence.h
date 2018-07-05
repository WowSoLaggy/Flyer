#pragma once

#include "Material.h"


struct MaterialSpan
{
  Material material;

  int startIndex;
  int count;
};

class MaterialSequence
{
public:

  void clear();
  void add(const MaterialSpan& i_materialSpan);

  std::vector<MaterialSpan> getMaterialSpans();

private:

  std::vector<MaterialSpan> d_materialSpans;
};
