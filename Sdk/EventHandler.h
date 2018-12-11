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
  
  std::vector<EventHandlerRef> d_clients;
  std::vector<EventHandlerRef> d_servers;

};
