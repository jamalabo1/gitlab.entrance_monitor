//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_H

#include <string>
#include <core/init.h>
#include <core/amqp.h>
#include "publisher.h"

namespace core::communication::publish {

    class PublisherFactory {
    public:
        virtual std::unique_ptr<Publisher>
        create_publisher(const std::string &exchange_name, amqp::ArgsTable args = {}) const = 0;
    };

    using $PublisherFactory = $Exported<PublisherFactory>;
    using PublisherFactoryComponent = ExportCoreComponentWithRequired(ExportRequiredComponents($Publisher),
                                                                      $PublisherFactory);

    PublisherFactoryComponent getCommunicationPublisherFactoryComponent();
}
#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_H
