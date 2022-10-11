//
// Created by jamal on 16/08/2022.
//
#include <core/logging.h>
#include "publisher_impl.h"

using namespace fruit;
using namespace std;
using namespace core::amqp;
using namespace core::communication::publish;
using namespace core::communication::publish::impl;

PublisherImpl::PublisherImpl(ASSISTED(std::string) exchange_name, unique_factory(amqp::ChannelHolder) channel_factory) :
exchange_name(std::move(exchange_name)) {
    channel = channel_factory();
}

void PublisherImpl::publish_message(const std::vector<uint8_t> &data) const {
//    shared_ptr<BasicMessage> message = make_shared<BasicMessage>(data);

    BOOST_LOG_TRIVIAL(trace) << "publishing message with size: " << data.size() * sizeof(uint8_t);

//    char *cdata = new char[data.size()];
//    std::copy(data.begin(), data.end(), cdata);

    std::string sdata(data.begin(), data.end());


    bool result = CCD(channel)->publish(exchange_name, "", sdata);

    BOOST_LOG_TRIVIAL(trace) << "publishing message to `" << exchange_name << "` resulted in :" << result;
}

PublisherComponent core::communication::publish::getCommunicationPublisherComponent() {
    return fruit::createComponent()
            .install(getAmqpChannelComponent)
            .bind<Publisher, PublisherImpl>();
}