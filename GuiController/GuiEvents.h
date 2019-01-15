#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <Sdk/IEvent.h>


class GuiAddedEvent : public IEvent
{
public:

  GuiAddedEvent(IGuiPtr i_gui)
    : d_gui(i_gui)
  {
  }

  IGuiPtr getGui() const { return d_gui; }

private:

  IGuiPtr d_gui;
};


class GuiDeletedEvent : public IEvent
{
public:

  GuiDeletedEvent(IGuiPtr i_gui)
    : d_gui(i_gui)
  {
  }

  IGuiPtr getGui() const { return d_gui; }

private:

  IGuiPtr d_gui;
};


class GuiResourcesChanged : public IEvent
{
public:
  GuiResourcesChanged(IGuiPtr i_gui)
    : d_gui(i_gui)
  {
  }

  IGuiPtr getGui() const { return d_gui; }

private:
  IGuiPtr d_gui;
};
