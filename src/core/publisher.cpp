//
// Created by jamal on 02/07/2022.
//
#include <core/publisher.h>
#include <core/ptrs.h>
#include <core/logging.h>

using namespace std;
using namespace core::publish;


void Publisher::publish(const vector<uint8_t> &data) const {
//    const string s(data.begin(), data.end());

    BOOST_LOG_TRIVIAL(trace) << "publishing message from publisher";

    publish_message(data);

    BOOST_LOG_TRIVIAL(trace) << "message was publisher successfully";
}

