//
// Created by jamal on 02/07/2022.
//

#include "publisher_factory.h"

#include "amqp.h"


namespace core::communication::publish {

    namespace impl {

        PublisherFactoryImpl::PublisherFactoryImpl(unique_factory(amqp::ChannelHolder) channel_factory,
                                                   PublisherFactoryImpl::publisher_factory_t &publisher_factory)
                : m_publisher_factory(publisher_factory) {
            m_channel = channel_factory();
        }

/***
 * @param exchange_name exchange name to publish messages to.
 * @returns a publisher "instance" (unique_ptr) for message s to be published to, this enables hiding the amqp implementation from the task handlers, which allows future changing in messaging broker.
 * */
        unique_ptr<Publisher>
        PublisherFactoryImpl::create_publisher(const std::string &exchange_name, amqp::ArgsTable args) const {
            // note: connection is injected by the DI, the DI is responsible for connection creation to allow standalone (executable) & shared (lib) usage of the factory.

            // declare exchange for producer to publish messages to.
            CCD(m_channel)->declareExchange(exchange_name, AMQP::ExchangeType::fanout, to_table(args));

            // create unique_ptr to hand ownership to the caller.
            return m_publisher_factory(exchange_name);
        }
    }


    PublisherFactoryComponent getCommunicationPublisherFactoryComponent() {
        return fruit::createComponent()
                .install(amqp::getAmqpChannelComponent)
                .bind<PublisherFactory, impl::PublisherFactoryImpl>();
    }
}


