#pragma once

#include <Sdk/SdkFwd.h>


// GUI

using GuiId = UniqueId;
class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;


// GUI2d

struct GuiCollection;

class IGui2d;
using IGui2dPtr = std::shared_ptr<IGui2d>;
using IGui2dPtrs = std::vector<IGui2dPtr>;

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
