#pragma once

#include <Sdk/SdkFwd.h>


// GUI

struct GuiCollection;
using GuiId = UniqueId;

class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;

class Label;
class Panel;
class HealthBar;
class CurrentActionPanel;


// HUD

struct HudCollection;
using HudId = UniqueId;

class IHud;
using IHudPtr = std::shared_ptr<IHud>;
using IHudPtrs = std::vector<IHudPtr>;

class CircleHud;
