//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PUBLISHER_H
#define ENTRANCE_MONITOR_V2_PUBLISHER_H

#include <core/ptrs.h>
#include <core/msgpacker.h>

namespace core::publish {


    class Publisher {
    protected:

        virtual void publish_message(const std::vector<uint8_t> &data) const = 0;


    public:
        void publish(const std::vector<uint8_t> &data) const;

        template<typename T>
        void publish(T &packable_object) const {
            auto vector = core::msgpacker::pack(packable_object);
            publish_message(vector);
        }
    };

}

#endif //ENTRANCE_MONITOR_V2_PUBLISHER_H
