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


// HUD

struct HudCollection;

class IHud;
using IHudPtr = std::shared_ptr<IHud>;
using IHudPtrs = std::vector<IHudPtr>;

class CollisionShapeHud;
