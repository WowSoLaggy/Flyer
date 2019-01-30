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

enum class ShapeType;
class IShape;
using IShapePtr = std::shared_ptr<IShape>;
class Circle;
class Aabb;

class IAction;
using IActionPtr = std::shared_ptr<IAction>;
