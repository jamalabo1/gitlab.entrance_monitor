//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_SERVICE_H
#define ENTRANCE_MONITOR_V2_SERVICE_H

#include <core/communication/consume.h>
#include <core/cancellation_token.h>
#include <boost/asio.hpp>


#define CREATE_CONSUMER_SERVICE_RUNNER(...) \
core::consume::ConsumeOptions options(handler, token, __VA_ARGS__);           \
post([this, &options]() { \
consumer->consume(options); \
}) \

#endif //ENTRANCE_MONITOR_V2_SERVICE_H
