//
// Created by jamal on 03/07/2022.
//

#include <object_detector/object_detector.h>
#include <frame_message_handler.h>
#include <utils/service.h>

using namespace fruit;
using namespace core;
using namespace core::amqp;


ObjectDetector::ObjectDetector(core::consume::Consumer *consumer, core::consume::ConsumerMessageHandler *handler,
                               core::IoRunner *io_runner) : TaskService(io_runner), consumer(consumer),
                                                            handler(handler) {

}

int ObjectDetector::setup() {

    ArgsTable args = {
            {"x-max-length", 5} // MAX ACCUMULATIVE QUEUE SIZE IS 5,
            // This ~means the max latency in the _queue is 5 frames.
    };

    CREATE_CONSUMER_SERVICE_RUNNER("frames.{1}", args, true);

    return run();
}


ObjectDetectorComponent getObjectDetectorComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getFrameMessageHandlerComponent)
            .addMultibinding<TaskService, ObjectDetector>();
}
