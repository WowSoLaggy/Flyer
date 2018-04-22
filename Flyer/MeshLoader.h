#pragma once

#include "Utils.h"
#include "VertexTypes.h"


class MeshLoader
{
public:

  static void loadMeshInfoFromFile(
    const std::string& i_filePath,
    std::vector<VertexTypePosTexNorm>& o_vertices,
    std::vector<int>& o_indices);

};
