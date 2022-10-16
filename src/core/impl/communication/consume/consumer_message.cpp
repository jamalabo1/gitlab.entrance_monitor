//
// Created by jamal on 16/08/2022.
//
#include "consumer_message.h"

namespace core::communication::consume::impl {

    std::string ConsumerMessageImpl::Body() {
        const char *data = envelope->body();
        uint64_t size = envelope->bodySize();

        return {data, size};
    }

}

