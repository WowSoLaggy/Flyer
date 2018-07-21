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

  const std::vector<MaterialSpan>& getMaterialSpans() const;

private:

  std::vector<MaterialSpan> d_materialSpans;
};
