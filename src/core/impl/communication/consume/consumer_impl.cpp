//
// Created by jamal on 26/07/2022.
//
#include "consumer_impl.h"
#include <core/cancellation_token.h>
#include "consumer_message.h"
#include "amqp.h"

#include <core/logging.h>

using namespace std;
using namespace core;
using namespace core::amqp;
using namespace core::communication::consume;
using namespace core::communication::consume::impl;

void ConsumerImpl::consume(const ConsumeOptions& options) {


    auto startCb = [](const std::string &consumertag) {
        BOOST_LOG_TRIVIAL(trace) << "consume operation started with consumer tag: " << consumertag;
    };

    auto c = channel->operator->().get();
    // cop
    auto ack = [c](uint64_t dtag) {
        c->ack(dtag);
    };

    // callback operation when a message was received
    auto messageCb = [ack, &options](const AMQP::Message &message, uint64_t deliveryTag, bool redelivered) {

        BOOST_LOG_TRIVIAL(trace) << "consume message received";

        {
            auto handlerMessage = ConsumerMessageImpl::Create(&message);
            (*options.handler)(handlerMessage);
        }

        // acknowledge the message
        ack(deliveryTag);
    };

    auto errorCb = [](auto err) {
        BOOST_LOG_TRIVIAL(trace) << "error on consume";
    };


    BOOST_LOG_TRIVIAL(trace) << "consume operation called";

    auto setup_consumer = [=](std::string queue_name) {
        if(options.is_work_queue) {
            c->setQos(1);
        }

        c->consume(queue_name)
                .onReceived(messageCb)
                .onSuccess(startCb)
                .onError(errorCb);
    };

    std::string exchange_name = options.exchange_name;
    CCD(channel)->declareExchange(exchange_name, AMQP::ExchangeType::fanout);

    string d_queue_name;
    int queue_flags;
    if(options.is_work_queue) {
        d_queue_name = exchange_name;
        queue_flags = AMQP::durable;
    } else {
        d_queue_name = "";
        queue_flags = AMQP::autodelete + AMQP::exclusive;
    }

    CCD(channel)->declareQueue(d_queue_name, queue_flags, to_table(options.args))
            .onSuccess([&, exchange_name](const std::string &queue_name, uint32_t messagecount, uint32_t consumercount) {

                BOOST_LOG_TRIVIAL(trace) << "declared exchange " << exchange_name << " with queue " << queue_name;

                //exchange_name, queue_name
                CCD(channel)->bindQueue(exchange_name, queue_name, "/")
                        .onSuccess([=]() {
                            BOOST_LOG_TRIVIAL(trace) << "creating consumer on exchange" << exchange_name
                                                     << " with queue " << queue_name;
                            setup_consumer(queue_name);
                        }).onError([](auto err) {
                            BOOST_LOG_TRIVIAL(fatal) << "error at bindQueue";
                        });
            })
            .onError([](auto err) {
                BOOST_LOG_TRIVIAL(fatal) << "error at declareQueue";
            });
}

ConsumerComponent core::communication::consume::getCommunicationConsumeConsumerComponent() {
    return fruit::createComponent()
            .install(getAmqpChannelComponent)
            .bind<Consumer, ConsumerImpl>();
}
