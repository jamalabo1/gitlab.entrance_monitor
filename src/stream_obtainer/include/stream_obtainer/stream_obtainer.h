//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H

#include <core/core.h>

class StreamObtainer : public core::TaskService {
private:
    core::publish::PublisherFactory *publisher_factory;
    core::Configurations *configs;
public:
    INJECT(StreamObtainer(core::publish::PublisherFactory * publisher_factory, core::IoRunner* io_runner, core::Configurations * configurations));

    int setup() override;

    ~StreamObtainer();
};

using StreamObtainerComponent = fruit::Component<RequiredComponents, StreamObtainer>;

StreamObtainerComponent getStreamObtainerComponent();


#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H
