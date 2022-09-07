//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_MSGPACKER_H
#define ENTRANCE_MONITOR_V2_MSGPACKER_H

#include <system_error>

#include <core/string_utils.h>

#include <core/consumer_message.h>

#include <msgpack/msgpack.hpp>


namespace core::msgpacker {




    template<class T>
    T unpack(const std::vector<uint8_t> &data) {
        return msgpack::unpack<T>(data);
    }

    template<class T>
    T unpack(const std::string &data) {
        const std::vector<uint8_t> vector = string_to_vector(data);
        return unpack<T>(vector);
    }

    template<class T>
    T unpack(const core::consume::ConsumerMessage::ptr_t &message) {
        return unpack<T>(message->Body());
    }

    template<class T>
    std::vector<uint8_t> pack(T data) {
        return msgpack::pack(data);
    }
}


#endif //ENTRANCE_MONITOR_V2_MSGPACKER_H
