//
// Created by jamal on 02/07/2022.
//

#include <core/init.h>

#include "impl/publisher_factory.h"

#include "publisher_impl.h"

#include <string>
#include "amqp.h"


using namespace AMQP;
using namespace core;
using namespace core::impl;
using namespace core::amqp;
using namespace core::publish;

/***
 * @param exchange_name exchange name to publish messages to.
 * @returns a publisher "instance" (unique_ptr) for messages to be published to, this enables hiding the amqp implementation from the task handlers, which allows future changing in messaging broker.
 * */
unique_ptr<Publisher> PublisherFactoryImpl::create_publisher(const std::string &exchange_name, ArgsTable args) {
    // note: connection is injected by the DI, the DI is responsible for connection creation to allow standalone (executable) & shared (lib) usage of the factory.

    // declare exchange for producer to publish messages to.
    CCD(channel)->declareExchange(exchange_name, ExchangeType::fanout, to_table(args));

    // create unique_ptr to hand ownership to the caller.
    return std::make_unique<PublisherImpl>(channel, exchange_name);
}


PublisherFactoryComponent publish::getPublisherFactoryComponent() {
    return fruit::createComponent()
            .install(getAmqpComponent)
            .bind<PublisherFactory, PublisherFactoryImpl>();
}
