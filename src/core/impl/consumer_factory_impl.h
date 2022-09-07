//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_IMPL_H
#define ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_IMPL_H

#include <core/init.h>
#include "channel_holder.h"
#include <core/consumer_factory.h>
#include <utility>

//typedef std::function<std::unique_ptr<Consumer>(std::string)> consumer_factory_t;

//class ConsumerFactoryImpl : public ConsumerFactory {
//private:
//    shared_ptr<ChannelHolder> channel;
////    consumer_factory_t consumer_factory;
//    shared_ptr<Consumer> consumer;
//
//public:
//    INJECT(ConsumerFactoryImpl(shared_factory(ChannelHolder) channel_factory, unique_factory(Consumer, std::shared_ptr<ChannelHolder>) consumer_factory)) {
//        channel = channel_factory();
//        consumer = consumer_factory(channel);
//    }
//
//    CreateConsumerCb create_consumer(const std::string &exchange_name, ArgsTable args) override;
//};


#endif //ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_IMPL_H
