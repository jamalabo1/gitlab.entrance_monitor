//
// Created by jamal on 03/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
#define ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H

//#include <functional>
#include <core/init.h>

#include <amqpcpp.h>

// CCD = CORE CHANNEL DEFERRED
#define CCD(x) (*x)

namespace core::amqp {


    class ChannelHolder {
    public:

        virtual ~ChannelHolder() = default;

        virtual shared_ptr <AMQP::Channel> operator*() const = 0;

        virtual shared_ptr <AMQP::Channel> operator->() const = 0;

//    virtual std::string BasicConsume(std::string) = 0;
//
//    virtual std::string BasicConsume(std::string, std::string) = 0;
//
//    virtual Envelope::ptr_t BasicConsumeMessage(std::string) = 0;

//    virtual void BasicAck(const Envelope::ptr_t &) = 0;
//
//    virtual void DeclareExchange(std::string, std::string) = 0;
//
//    virtual void DeclareExchange(std::string, std::string, Table) = 0;
//
//    virtual void BasicPublish(std::string, std::string, shared_ptr<BasicMessage>) = 0;
//
//    virtual std::string DeclareQueue(std::string) = 0;
//
//    virtual void BindQueue(std::string, std::string) = 0;
//
//    virtual std::string DeclareQueue(const std::string &queue_name, bool passive,
//                                     bool durable, bool exclusive, bool auto_delete,
//                                     const Table &arguments) = 0;
    };

    using AmqpComponent = fruit::Component<RequiredComponents, ChannelHolder, std::function<std::unique_ptr<ChannelHolder>()>>;

    AmqpComponent getAmqpComponent();
}

#endif //ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
