#pragma once

#include <GuiModel/GuiModelFwd.h>
#include <LaggySdk/IEvent.h>


class GuiAddedEvent : public Sdk::IEvent
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


class GuiDeletedEvent : public Sdk::IEvent
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


class GuiResourcesChanged : public Sdk::IEvent
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
