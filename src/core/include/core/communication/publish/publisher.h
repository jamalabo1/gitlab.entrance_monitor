//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_PUBLISHER_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_PUBLISHER_H

#include <core/init.h>
#include <core/msgpacker.h>

namespace core::communication::publish {


    class Publisher {
    protected:
        virtual void publish_message(const std::vector<uint8_t> &data) const = 0;

    public:
        virtual ~Publisher() = default;

        void publish(const std::vector<uint8_t> &data) const;

        template<typename T>
        void publish(T &packable_object) const {
            auto vector = core::msgpacker::pack(packable_object);
            publish_message(vector);
        }

        template<typename T>
        void publish_pb(T &packable_object) const {
            std::string data;
            packable_object.SerializeToString(&data);

//            auto vector = core::msgpacker::pack(packable_object);
            publish_message(string_to_vector(data));
        }
    };

    // publisher is a class that is initiated with a string value supplied to it.
    using Factory = MakeUniqueFactoryP(Publisher, std::string);
    // $ prefix is to mark all types that are made to be exported.
    // for example the publisher class is not exportable (to components) because it contains ASSISTED type
    // this requires another type to be exported.
    using $Publisher = $Exported<Factory>;
    using PublisherComponent = ExportCoreComponent($Publisher);

    PublisherComponent getCommunicationPublisherComponent();
}

#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_PUBLISHER_H
