//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_H
#define ENTRANCE_MONITOR_V2_CONSUMER_H

#include <core/init.h>
#include <core/consumer_message_handler.h>
#include <core/cancellation_token.h>
#include <core/amqp.h>

#include <utility>

namespace core::consume {


    struct ConsumeOptions {

        ConsumeOptions(ConsumerMessageHandler* handler,
                       CancellationToken &token, std::string exchange_name, amqp::ArgsTable args = {}, bool is_work_queue=false) :
                handler(handler),
                token(token),
                exchange_name(std::move(exchange_name)),
                args(std::move(args)),
                is_work_queue(is_work_queue)
                {}

        std::string exchange_name;
        amqp::ArgsTable args;
        CancellationToken &token;
        ConsumerMessageHandler* handler;
        bool is_work_queue;
    };

    class Consumer {
    public:

        virtual ~Consumer() = default;

        virtual void
        consume(const ConsumeOptions &) = 0;
    };

//using ConsumerFactory_t = std::function<std::shared_ptr<Consumer>(std::shared_ptr<ChannelHolder>)>;

    using ConsumerComponent = fruit::Component<RequiredComponents, Consumer>;

    ConsumerComponent getConsumerComponent();
}

#endif //ENTRANCE_MONITOR_V2_CONSUMER_H
