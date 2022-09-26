//
// Created by jamal on 15/08/2022.
//
#include <core/logging.h>
#include "blockage_result_message_handler.h"
#include <view_models/blocking_result_view.h>
#include <core/msgpacker.h>

using namespace core;
using namespace core::communication::consume;
using namespace core::msgpacker;


void BlockageResultMessageHandler::operator()(const ConsumerMessage::ptr_t &envelope) const {

    auto view = unpack<BlockingResultView>(envelope);

    BOOST_LOG_TRIVIAL(debug) << "blocking result message was received with result: " << view.result;
    // is blocking
    if (view.result) {
        sound_controller->play();
    } else {
        sound_controller->stop();
    }
}

BlockageResultMessageHandler::BlockageResultMessageHandler(SoundController *sound_controller) : sound_controller(
        sound_controller) {

}

BlockageResultMessageHandlerComponent getBlockageResultMessageHandlerComponent() {
    return fruit::createComponent()
            .install(getSoundControllerComponent)
            .bind<ConsumerMessageHandler, BlockageResultMessageHandler>();
}
