//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STANDALONE_H
#define ENTRANCE_MONITOR_V2_STANDALONE_H

#include <core/logging.h>
#include <fruit/fruit.h>
#include <boost/asio.hpp>
#include <core/logging.h>

#ifdef WIN32

#include <WinBase.h>

#endif


void init_service_runner() {

#ifdef WIN32
    // The following sets the appropriate flags to prevent system to go into sleep mode.
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
#endif

    BOOST_LOG_TRIVIAL(info) << "initiation service runner";

#if NDEBUG
    boost::log::core::get()->set_filter
            (
                    boost::log::trivial::severity >= boost::log::trivial::trace
            );
#endif
}

#define BUILD_STANDALONE_FROM_SERVICE(getRootComponent) int main() { \
init_service_runner();\
fruit::Injector injector(getRootComponent);                          \
BOOST_LOG_TRIVIAL(info) << "Running as standalone"; \
BOOST_LOG_TRIVIAL(trace) << "getting `TaskService` from injector"; \
const std::vector<TaskService *> &services = injector.getMultibindings<TaskService>(); \
BOOST_LOG_TRIVIAL(trace) << "creating thread pool with size " << services.size(); \
boost::asio::thread_pool pool(services.size()); \
for (const auto &service: services) { \
BOOST_LOG_TRIVIAL(trace) << "posting service to thread pool"; \
boost::asio::post(pool, [&service] {                                 \
service->setup();                                                      \
BOOST_LOG_TRIVIAL(trace) << "service runner finished"; \
}); \
}\
BOOST_LOG_TRIVIAL(trace) << "joining pool threads"; \
pool.join();                                                         \
BOOST_LOG_TRIVIAL(trace) << "thread pool finished"; \
return -1; \
}\


#endif //ENTRANCE_MONITOR_V2_STANDALONE_H
