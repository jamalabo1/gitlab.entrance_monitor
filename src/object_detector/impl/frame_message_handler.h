//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_FRAME_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_FRAME_MESSAGE_HANDLER_H

#include <fruit/fruit.h>
#include <core/consumer_message_handler.h>
#include <core/publisher_factory.h>
#include <core/gui_handler.h>

#include "detector.h"

class FrameMessageHandler : public core::consume::ConsumerMessageHandler {
private:
    Detector *detector;
    unique_ptr<core::publish::Publisher> publisher;
    core::GUIHandler *gui_handler;
public:
    INJECT(FrameMessageHandler(Detector * detector, core::publish::PublisherFactory * publisher_factory,
                               core::GUIHandler * guiHandler));

    void operator()(const core::consume::ConsumerMessage::ptr_t &envelope) const override;
};

using FrameMessageHandlerComponent = fruit::Component<MakeRequiredComponents(core::publish::PublisherFactory, core::IoRunner, core::GUIHandler), core::consume::ConsumerMessageHandler>;

FrameMessageHandlerComponent getFrameMessageHandlerComponent();

#endif //ENTRANCE_MONITOR_V2_FRAME_MESSAGE_HANDLER_H
