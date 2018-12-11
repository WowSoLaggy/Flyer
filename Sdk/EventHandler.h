#pragma once

#include "SdkFwd.h"


class EventHandler
{
public:

  virtual ~EventHandler();

  virtual void processEvent(const IEvent& i_event) { };

  virtual void notify(const IEvent& i_event) final;
  virtual void connectTo(EventHandler& i_handler) final;
  virtual void disconnectFrom(EventHandler& i_handler) final;
  virtual void disconnectFromAll() final;

private:

  using EventHandlerRef = std::reference_wrapper<EventHandler>;
  using EventHandlerRefs = std::vector<EventHandlerRef>;
  
  EventHandlerRefs d_clients;
  EventHandlerRefs d_servers;

};
