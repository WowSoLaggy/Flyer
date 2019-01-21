#pragma once

#include <Sdk/SdkFwd.h>


class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;

class IHud;
using IHudPtr = std::shared_ptr<IHud>;
using IHudPtrs = std::vector<IHudPtr>;

class Label;
class Panel;
class HealthBar;
class CurrentActionPanel;

class GuiCollection;
using GuiId = UniqueId;
