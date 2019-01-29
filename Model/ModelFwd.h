#pragma once

class World;
class Terrain;

class Object;
using ObjectPtr = std::shared_ptr<Object>;
using ObjectPtrs = std::vector<ObjectPtr>;

class Creature;
using CreaturePtr = std::shared_ptr<Creature>;

class IShape;
using IShapePtr = std::shared_ptr<IShape>;
class Circle;

class IAction;
using IActionPtr = std::shared_ptr<IAction>;
