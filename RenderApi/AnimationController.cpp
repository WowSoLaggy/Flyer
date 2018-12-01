#include "stdafx.h"
#include "AnimationController.h"

#include "MeshResourceCmo.h"
#include "ResourceController.h"


AnimationController::AnimationController(const IResourceController& i_resourceController, ResourceId i_resourceId)
  : d_model(
      dynamic_cast<const ResourceController&>(i_resourceController).getMeshResourceCmo(i_resourceId).getModel())
  , d_currentAnimationName(L"")
  , d_animationTime(0)
{
  for (auto& modelMeshPtr : d_model.meshes)
  {
    BoneTransformCollection boneTransformCollection(modelMeshPtr->bones.size());
    d_meshesBoneTransforms.push_back(std::move(boneTransformCollection));
  }

  resetTransforms();
}


void AnimationController::setAnimation(std::wstring i_animationName)
{
  d_currentAnimationName = std::move(i_animationName);
  d_animationTime = 0;

  resetTransforms();
}


void AnimationController::update(double i_dt)
{
  d_animationTime += i_dt;

  resetTransforms();

  for (int meshIndex = 0; meshIndex < d_model.meshes.size(); ++meshIndex)
  {
    const auto& mesh = d_model.meshes.at(meshIndex);

    auto itAnim = mesh->animClipMap.find(L"MyBone|" + d_currentAnimationName);
    if (itAnim == mesh->animClipMap.end())
      continue;

    double animLength = itAnim->second.EndTime - itAnim->second.StartTime;
    double time = d_animationTime;
    while (time > animLength)
      time -= animLength;

    for (const auto& keyframe : itAnim->second.Keyframes)
    {
      if (keyframe.Time > time)
        break;

      d_meshesBoneTransforms.at(meshIndex).at(keyframe.BoneIndex) = keyframe.Transform;
    }
  }
}


void AnimationController::resetTransforms()
{
  for (int meshIndex = 0; meshIndex < d_model.meshes.size(); ++meshIndex)
  {
    const auto& mesh = d_model.meshes.at(meshIndex);
    for (int boneIndex = 0; boneIndex < (int)mesh->bones.size(); ++boneIndex)
      d_meshesBoneTransforms.at(meshIndex).at(boneIndex) = mesh->bones.at(boneIndex).LocalTransform;
  }
}


XMMATRIX AnimationController::getTransform() const
{
  XMMATRIX m = XMMatrixIdentity();

  if (!d_meshesBoneTransforms.empty() && !d_meshesBoneTransforms.front().empty())
    m = d_meshesBoneTransforms.front().front();

  return m;
}
