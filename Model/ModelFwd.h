#pragma once

class World;
class Terrain;

using ObjectId = int;
class Object;
using ObjectPtr = std::shared_ptr<Object>;
using ObjectPtrs = std::vector<ObjectPtr>;

class Creature;
using CreaturePtr = std::shared_ptr<Creature>;

class IRealObject;
using IRealObjectPtr = std::shared_ptr<IRealObject>;
using IRealObjectPtrs = std::vector<IRealObjectPtr>;

class IAction;
