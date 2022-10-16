//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_CONSUMER_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_CONSUMER_H


#include <core/init.h>
#include <core/cancellation_token.h>
#include <core/amqp.h>
#include "consumer_message_handler.h"


namespace core::communication::consume {


    struct ConsumeOptions {

        ConsumeOptions(ConsumerMessageHandler *handler,
                       shared_ptr<CancellationToken> token, std::string exchange_name, amqp::ArgsTable args = {},
                       bool is_work_queue = false) :
                handler(handler),
                token(token),
                exchange_name(std::move(exchange_name)),
                args(std::move(args)),
                is_work_queue(is_work_queue) {}

        std::string exchange_name;
        amqp::ArgsTable args;
        shared_ptr<CancellationToken> token;
        ConsumerMessageHandler *handler;

        //        shared_ptr<ConsumerMessageHandler> handler;
        bool is_work_queue;
    };

    class Consumer {
    public:

        virtual ~Consumer() = default;

        virtual void
        consume(const ConsumeOptions &) = 0;
    };

    using $ConsumerComponent = $Exported<Consumer>;
    using ConsumerComponent = $ConsumerComponent::PureComponent;

    ConsumerComponent getCommunicationConsumeConsumerComponent();
}

#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_CONSUMER_H
