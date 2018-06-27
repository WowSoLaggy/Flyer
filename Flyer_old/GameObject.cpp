#include "stdafx.h"
#include "GameObject.h"

#include "RenderDevice.h"
#include "Utils.h"


void GameObject::setResourceNames(const std::string& i_modelName, const std::string& i_textureName)
{
  d_modelName = i_modelName;
  d_textureName = i_textureName;
}


void GameObject::load(RenderDevice& i_renderDevice, const ResourceController& i_resourceController)
{
  updateWorldMatrix();
  d_modelResourceId = i_resourceController.getResourceId(d_modelName);
  loadTexture(i_renderDevice);
}

void GameObject::unload()
{
  unloadTexture();
}


void GameObject::render(RenderDevice& i_renderDevice, RenderFunc i_renderFunc) const
{
  i_renderFunc(*this);
}


void GameObject::loadTexture(RenderDevice& i_renderDevice)
{
  CreateDDSTextureFromFile(i_renderDevice.getDevicePtr(),
    Utils::getWString(d_textureName).c_str(), nullptr, &d_texture);
}

void GameObject::unloadTexture()
{
  d_texture->Release();
}


void GameObject::setPosition(XMFLOAT3 i_position)
{
  d_position = i_position;
  updateWorldMatrix();
}

void GameObject::updateWorldMatrix()
{
  d_worldMatrix = XMMatrixTranslation(d_position.x, d_position.y, d_position.z);
}


ResourceId GameObject::getModelResourceId() const
{
  return d_modelResourceId;
}
