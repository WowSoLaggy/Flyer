#pragma once

class IGui;
using IGuiPtr = std::shared_ptr<IGui>;
using IGuiPtrs = std::vector<IGuiPtr>;

class Label;
class Panel;
class HealthBar;

class GuiCollection;
using GuiId = int;
