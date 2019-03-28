#pragma once

#include "Message.h"


using MessageHandler = std::function<void(Message)>;

bool handleMessages(MessageHandler i_messageHandler);
