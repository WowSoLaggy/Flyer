#include "stdafx.h"
#include "TerrainVm.h"

#include <Model/Terrain.h>
#include <LaggyDx/IRenderer3d.h>
#include <LaggyDx/IResourceController.h>


TerrainVm::TerrainVm(
  IRenderDevice& io_renderDevice, const IResourceController& i_resourceController,
  const Terrain& i_terrain)
  : d_terrain(i_terrain)
  , d_textureResourceId(i_resourceController.getResourceId(d_terrain.getTextureName()))
{
  createBuffers(io_renderDevice);
}

TerrainVm::~TerrainVm()
{
  d_vertexBuffer.dispose();
  d_indexBuffer.dispose();
}


void TerrainVm::render(IRenderer3d& i_renderer) const
{
  i_renderer.renderObject(
    d_textureResourceId,
    d_vertexBuffer, d_indexBuffer,
    d_materialSequence.getMaterialSpans(),
    Sdk::Vector3::zero(), Sdk::Vector3::zero());
}


void TerrainVm::createBuffers(IRenderDevice& io_renderDevice)
{
  auto& heightMap = d_terrain.getHeightMap();
  float heightGridStep = d_terrain.getHeightGridStep();
  
  int sizeX = heightMap.getSizeXInc();
  int sizeZ = heightMap.getSizeZInc();

  std::vector<VertexTypePosTexNorm> vertices;
  std::vector<int> indices;

  vertices.reserve(sizeX * sizeZ);
  indices.reserve((sizeX - 1) * (sizeZ - 1) * 2);


  auto getNorm1 = [&](int x, int z)
  {
    float height = heightMap.getHeight(x, z);
    Sdk::Vector3 v1{ 0, height - heightMap.getHeight(x, z - 1), -1 };
    Sdk::Vector3 v2{ -1, height - heightMap.getHeight(x - 1, z), 0 };
    return Sdk::normalize(cross(v1, v2));
  };

  auto getNorm2 = [&](int x, int z)
  {
    float height = heightMap.getHeight(x, z);
    Sdk::Vector3 v1{ 1, height - heightMap.getHeight(x + 1, z), 0 };
    Sdk::Vector3 v2{ 0, height - heightMap.getHeight(x, z - 1), -1 };
    return Sdk::normalize(cross(v1, v2));
  };

  auto getNorm3 = [&](int x, int z)
  {
    float height = heightMap.getHeight(x, z);
    Sdk::Vector3 v1{ 0, height - heightMap.getHeight(x, z + 1), +1 };
    Sdk::Vector3 v2{ 1, height - heightMap.getHeight(x + 1, z), 0 };
    return Sdk::normalize(cross(v1, v2));
  };

  auto getNorm4 = [&](int x, int z)
  {
    float height = heightMap.getHeight(x, z);
    Sdk::Vector3 v1{ -1, height - heightMap.getHeight(x - 1, z), 0 };
    Sdk::Vector3 v2{ 0, height - heightMap.getHeight(x, z + 1), +1 };
    return Sdk::normalize(cross(v1, v2));
  };


  auto addVertice = [&](int x, int z)
  {
    Sdk::Vector3 pos = { x * heightGridStep, heightMap.getHeight(x, z), z * heightGridStep };
    Sdk::Vector2 uv = { x * heightGridStep, z * heightGridStep };

    Sdk::Vector3 norm = { 0, 0, 0 };
    if (x > 0 && z > 0)
      norm += getNorm1(x, z);
    if (x < sizeX - 1 && z > 0)
      norm += getNorm2(x, z);
    if (x < sizeX - 1 && z  < sizeZ - 1)
      norm += getNorm3(x, z);
    if (x > 0 && z  < sizeZ - 1)
      norm += getNorm4(x, z);

    vertices.push_back({ pos, uv, normalize(norm) });
  };

  auto addIndices = [&](int x, int z)
  {
    /**

    We are operating the RH coordinate system (see pic below, Y-axis goes towards us)
    For the following square:

        (0, 0) *---* (1, 0) ----> X-axis
               | \ |
        (0, 1) *---* (1, 1)
               |
               |
               v Z-axis

    We are creating two CCW triangles:
      t1: (0, 0); (1, 1); (1, 0)
      t2: (0, 0); (0, 1); (1, 1)
    
    */

    // t1:
    indices.push_back(x + z * sizeX);
    indices.push_back((x + 1) + (z + 1) * sizeX);
    indices.push_back((x + 1) + z * sizeX);

    // t2:
    indices.push_back(x + z * sizeX);
    indices.push_back(x + (z + 1) * sizeX);
    indices.push_back((x + 1) + (z + 1) * sizeX);
  };


  for (int z = 0; z < sizeZ; ++z)
  {
    for (int x = 0; x < sizeX; ++x)
    {
      addVertice(x, z);

      // Don't add indices for the last row and col because it will be out of bounds
      if (x < sizeX - 1 && z < sizeZ - 1)
        addIndices(x, z);
    }
  }


  d_vertexBuffer.create(io_renderDevice, vertices);
  d_indexBuffer.create(io_renderDevice, indices);

  d_materialSequence.add({ Material::getDefault(), 0, d_indexBuffer.getIndexCount() });
}
