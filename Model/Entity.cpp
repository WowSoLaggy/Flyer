#include "stdafx.h"
#include "Entity.h"


ObjectId Entity::s_nextId = 0;


Entity::Entity()
  : d_id(s_nextId++)
  , d_modelName("")
  , d_customTextureName("")
  , d_position{ 0, 0, 0 }
  , d_rotation{ 0, 0, 0 }
  , d_visible(true)
{
}
