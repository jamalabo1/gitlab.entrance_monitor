//
// Created by jamal on 16/08/2022.
//
#include <core/logging.h>
#include "impl/publisher_impl.h"

using namespace core::amqp;
using namespace core::impl;

PublisherImpl::PublisherImpl(ChannelHolder *channel, const std::string exchange_name) : channel(channel),
                                                                                        exchange_name(
                                                                                                std::move(
                                                                                                        exchange_name)) {}

void PublisherImpl::publish_message(const std::vector<uint8_t> &data) const {
//    shared_ptr<BasicMessage> message = make_shared<BasicMessage>(data);

    BOOST_LOG_TRIVIAL(trace) << "publishing message with size: " << data.size() * sizeof(uint8_t);

//    char *cdata = new char[data.size()];
//    std::copy(data.begin(), data.end(), cdata);

    std::string sdata(data.begin(), data.end());


    bool result = CCD(channel)->publish(exchange_name, "", sdata);

    BOOST_LOG_TRIVIAL(trace) << "publishing message resulted in :" << result;

}