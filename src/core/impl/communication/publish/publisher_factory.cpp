//
// Created by jamal on 02/07/2022.
//

#include "publisher_factory.h"

#include "amqp.h"

using namespace AMQP;
using namespace core;
using namespace core::amqp;
using namespace core::communication::publish;
using namespace core::communication::publish::impl;


PublisherFactoryImpl::PublisherFactoryImpl(amqp::ChannelHolder *channel,
                                           PublisherFactoryImpl::publisher_factory_t &publisher_factory)
        : m_channel(channel), m_publisher_factory(publisher_factory) {
}

/***
 * @param exchange_name exchange name to publish messages to.
 * @returns a publisher "instance" (unique_ptr) for message s to be published to, this enables hiding the amqp implementation from the task handlers, which allows future changing in messaging broker.
 * */
unique_ptr<Publisher> PublisherFactoryImpl::create_publisher(const std::string &exchange_name, ArgsTable args) const {
    // note: connection is injected by the DI, the DI is responsible for connection creation to allow standalone (executable) & shared (lib) usage of the factory.

    // declare exchange for producer to publish messages to.
    CCD(m_channel)->declareExchange(exchange_name, ExchangeType::fanout, to_table(args));

    // create unique_ptr to hand ownership to the caller.
    return m_publisher_factory(exchange_name);
}


PublisherFactoryComponent core::communication::publish::getCommunicationPublisherFactoryComponent() {
    return fruit::createComponent()
            .install(getAmqpChannelComponent)
            .bind<PublisherFactory, PublisherFactoryImpl>();
}

