#pragma once

class World;
class Terrain;

class Object;
using ObjectPtr = std::shared_ptr<Object>;
using ObjectPtrs = std::vector<ObjectPtr>;

class IAction;

using ObjectId = int;
