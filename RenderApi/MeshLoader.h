#pragma once

#include "MaterialSequence.h"
#include "VertexTypes.h"


class MeshLoader
{
public:

  static void loadInfoFromFile(
    const std::string& i_modelPath, const std::string& i_materialsPath,
    std::vector<VertexTypePosTexNorm>& o_vertices, std::vector<int>& o_indices,
    MaterialSequence& o_matSequence);
};
