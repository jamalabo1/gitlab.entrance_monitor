//
// Created by jamal on 15/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKAGE_RESULT_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_BLOCKAGE_RESULT_MESSAGE_HANDLER_H

#include <core/init.h>
#include <core/consumer_message_handler.h>

#include <sound_controller.h>

class BlockageResultMessageHandler : public core::communication::consume::ConsumerMessageHandler {
private:
    SoundController*sound_controller;
public:
    INJECT(BlockageResultMessageHandler(SoundController * ));

    void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;
};

using BlockageResultMessageHandlerComponent = fruit::Component<RequiredComponents, core::communication::consume::ConsumerMessageHandler>;

BlockageResultMessageHandlerComponent getBlockageResultMessageHandlerComponent();

#endif //ENTRANCE_MONITOR_V2_BLOCKAGE_RESULT_MESSAGE_HANDLER_H
