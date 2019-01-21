#include "stdafx.h"
#include "Entity.h"


ObjectId Entity::s_nextId = 0;


Entity::Entity()
  : d_id(s_nextId++)
  , d_modelName("")
  , d_customTextureName("")
{
}
