#pragma once

#include <Sdk/SdkFwd.h>


using GuiId = UniqueId;


// GUI

struct GuiCollection;

class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;

class Label;
class Panel;
class HealthBar;
class CurrentActionPanel;


// GUI3d

struct Gui3dCollection;

class IGui3d;
using IGui3dPtr = std::shared_ptr<IGui3d>;
using IGui3dPtrs = std::vector<IGui3dPtr>;

class CollisionShapeGui3d;
