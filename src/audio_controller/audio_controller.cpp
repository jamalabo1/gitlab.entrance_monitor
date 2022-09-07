//
// Created by jamal on 14/08/2022.
//
#include "blockage_result_message_handler.h"
#include <audio_controller/audio_controller.h>
#include <utils/service.h>
#include <core/amqp/connection_factory.h>

using namespace fruit;
using namespace core;

AudioControllerService::AudioControllerService(core::consume::ConsumerMessageHandler *handler,
                                               core::consume::Consumer *consumer,
                                               core::IoRunner *io_runner) : TaskService(io_runner), handler(handler),
                                                                            consumer(consumer) {

}

int AudioControllerService::setup() {

    CREATE_CONSUMER_SERVICE_RUNNER("results.{1}");

    return run();
}


AudioControllerServiceComponent getAudioControllerServiceComponent() {
    return createComponent()
            .install(getBlockageResultMessageHandlerComponent)
            .install(getCoreComponents)
            .addMultibinding<TaskService, AudioControllerService>();
}