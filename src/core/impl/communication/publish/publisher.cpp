//
// Created by jamal on 02/07/2022.
//
#include <core/communication/publish.h>
#include <core/ptrs.h>
#include <core/logging.h>

namespace core::communication::publish {
    using std::vector;

    void Publisher::publish(const vector<uint8_t> &data) const {
        BOOST_LOG_TRIVIAL(trace) << "publishing message from publisher";

        publish_message(data);

        BOOST_LOG_TRIVIAL(trace) << "message was publisher successfully";
    }
}