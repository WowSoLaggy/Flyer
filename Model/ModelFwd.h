#pragma once

#include <memory>
#include <vector>


class World;
class Terrain;

class Object;
using ObjectPtr = std::shared_ptr<Object>;
using ObjectPtrs = std::vector<ObjectPtr>;

class Creature;
using CreaturePtr = std::shared_ptr<Creature>;

enum class ColShapeType;
class IColShape;
using IColShapePtr = std::shared_ptr<IColShape>;
class ColCircle;
class ColRect;

class IAction;
using IActionPtr = std::shared_ptr<IAction>;

enum class ControlledBy;
