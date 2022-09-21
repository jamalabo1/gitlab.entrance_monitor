//
// Created by jamal on 19/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_H

#include "publish/publisher.h"
#include "publish/publisher_factory.h"


namespace core::communication::publish {
    EXPORT_MODULE(getCommunicationPublishComponents, $PublisherFactory);
}


#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_H
