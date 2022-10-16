//
// Created by jamal on 16/08/2022.
//
#include <core/logging.h>
#include "publisher_impl.h"


namespace core::communication::publish {

    namespace impl {
        using std::string;
        using std::vector;

        PublisherImpl::PublisherImpl(ASSISTED(string) exchange_name,
                                     unique_factory(amqp::ChannelHolder) channel_factory) :
                exchange_name(std::move(exchange_name)) {
            channel = channel_factory();
        }

        void PublisherImpl::publish_message(const vector<uint8_t> &data) const {

            BOOST_LOG_TRIVIAL(trace) << "publishing message with size: " << data.size() * sizeof(uint8_t);

            string sdata(data.begin(), data.end());

            bool result = CCD(channel)->publish(exchange_name, "", sdata);

            BOOST_LOG_TRIVIAL(trace) << "publishing message to `" << exchange_name << "` resulted in :" << result;

        }
    }

    PublisherComponent getCommunicationPublisherComponent() {
        return fruit::createComponent()
                .install(amqp::getAmqpChannelComponent)
                .bind<Publisher, impl::PublisherImpl>();
    }
}
