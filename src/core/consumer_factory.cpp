////
//// Created by jamal on 26/07/2022.
////
//
//#include <core/consumer_factory.h>
//#include "impl/consumer_factory.h"
//#include "amqp.h"
//#include <core/logging.h>
//
//using namespace std;
//
//
//CreateConsumerCb ConsumerFactoryImpl::create_consumer(const std::string &exchange_name, ArgsTable args) {
//    //    std::string queue_name = amqp_channel->DeclareQueue(exchange_name, false);
//    CCD(channel)->declareExchange(exchange_name, AMQP::ExchangeType::fanout)
//    .onError([](auto err){
//        BOOST_LOG_TRIVIAL(fatal) << "error on declareExchange";
//    });
//    BOOST_LOG_TRIVIAL(trace) << "declaring exchange " << exchange_name;
//
//
//
//    return [&](const CancellationToken &token, const ConsumerMessageHandler &handler) {
////        AMQP::Table args;
////        args["x-queue-type"] = "exclusive";
//
//        CCD(channel)->declareQueue("", AMQP::exclusive + AMQP::autodelete)
//                .onSuccess([&](
//                        const std::string& queue_name,
//                        uint32_t messagecount,
//                        uint32_t consumercount
//                ) {
//
//                    BOOST_LOG_TRIVIAL(trace) << "declared exchange " << exchange_name << " with queue " << queue_name;
//
//                    CCD(channel)->bindQueue(exchange_name, queue_name, "/")
//                            .onSuccess([&token, &handler,  this, exchange_name, queue_name]() {
//                                BOOST_LOG_TRIVIAL(trace) << "creating consumer on exchange" << exchange_name << " with queue " << queue_name;
////                                auto consumer = consumer_factory(queue_name);
//                                consumer->consume(queue_name, token, handler);
//                            }).onError([](auto err) {
//                                BOOST_LOG_TRIVIAL(fatal) << "error at bindQueue";
//                            });
//                })
//                .onError([](auto err){
//                    BOOST_LOG_TRIVIAL(fatal) << "error at declareQueue";
//                });
//    };
//}
//
//ConsumerFactoryComponent getConsumerFactoryComponent() {
//    return fruit::createComponent()
//            .install(getAmqpComponent)
//            .install(getConsumerComponent)
//            .bind<ConsumerFactory, ConsumerFactoryImpl>();
//}
