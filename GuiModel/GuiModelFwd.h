#pragma once

#include <Sdk/SdkFwd.h>


class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;

class Label;
class Panel;
class HealthBar;
class CurrentActionPanel;

class GuiCollection;
using GuiId = UniqueId;
