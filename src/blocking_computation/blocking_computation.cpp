//
// Created by jamal on 13/08/2022.
//

#include <blocking_computation/blocking_computation.h>

#include <utils/service.h>

#include "detection_message_handler.h"

#include <boost/asio.hpp>

using namespace fruit;
using namespace core;
using namespace core::amqp;


BlockingComputationService::BlockingComputationService(core::communication::consume::ConsumerMessageHandler *handler,
                                                       core::communication::consume::Consumer *consumer,
                                                       core::IoRunner *io_runner) : Service(io_runner),
                                                                                    handler(handler),
                                                                                    consumer(consumer) {

}


int BlockingComputationService::setup() {

    ArgsTable args = {
            {
                    "x-max-length", 5
            }
    };

    CREATE_CONSUMER_SERVICE_RUNNER("detections.{1}", args, true);

    return run();
}


BlockingComputationComponent getBlockingComputationComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getDetectionMessageHandlerComponent)
            .addMultibinding<Service, BlockingComputationService>();
}