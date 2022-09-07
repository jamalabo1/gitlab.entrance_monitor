//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_IMPL_H
#define ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_IMPL_H

#include <amqpcpp.h>
#include <core/consumer_message.h>
#include <core/ptrs.h>

namespace core::impl {

    class ConsumerMessageImpl : public consume::ConsumerMessage {
    private:
        const AMQP::Message *envelope;
    public:
        explicit ConsumerMessageImpl(const AMQP::Message *envelope) : envelope(envelope) {}

        static ConsumerMessage::ptr_t Create(const AMQP::Message *env) {
            auto x = new ConsumerMessageImpl(env);
            return shared_ptr<ConsumerMessage>(x);
        }

        std::string Body() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_IMPL_H
