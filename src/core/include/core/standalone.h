//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
#define ENTRANCE_MONITOR_V2_CORE_STANDALONE_H

#include <core/init.h>
#include <core/logging.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include <core/service.h>
#include <core/io_context.h>


#ifdef WIN32

#include <WinBase.h>

#endif


void init_service_runner() {

#ifdef WIN32
    BOOST_LOG_TRIVIAL(debug) << "[WIN32]: setting thread type to continous";
   // The following sets the appropriate flags to prevent system to go into sleep mode.
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED);
#endif


#if APP_DEBUG
    boost::log::core::get()->set_filter
            (
                    boost::log::trivial::severity >= boost::log::trivial::trace
            );
#endif
}



int run_services(core::IoContext* io_context, const std::vector<core::Service *> &services) {

    auto post = [&](const std::function<void()>& func) {
        boost::asio::post(GET_BOOST_IO_CONTEXT(io_context), [&func](){
            func();
        });
    };

    for (const auto &service: services) {
        post([&]() {
            // setup service to register tasks.
            service->setup();

            // get registered tasks.
            auto tasks = service->getTasks();

            // loop over tasks
            for (const auto &task: tasks) {

                // post each task to the io_context.
                post([&]() {
                    task->operator()();
                });
            }
        });
    }

    boost::thread_group pool;
    for (auto i = 0u; i<boost::thread::hardware_concurrency(); ++i)
        pool.create_thread([&] {io_context->run(); });

    pool.join_all();

}

#define BUILD_STANDALONE_FROM_SERVICE(component)                                            \
int main() {                                                                                \
fruit::Injector injector(component);                                                        \
BOOST_LOG_TRIVIAL(info) << "initiation service runner";                                     \
init_service_runner();                                                                      \
BOOST_LOG_TRIVIAL(info) << "Running as standalone";                                         \
auto io_context = injector.get<core::IoContext*>();                                         \
BOOST_LOG_TRIVIAL(trace) << "getting `Service` from injector";                              \
const std::vector<core::Service *> &services = injector.getMultibindings<core::Service>();  \
run_services(io_context, services);                                                         \
}

//#define BUILD_STANDALONE_FROM_SERVICE(getRootComponent) int main() { \
//init_service_runner();\
//fruit::Injector injector(getRootComponent);                          \
//BOOST_LOG_TRIVIAL(info) << "Running as standalone"; \
//BOOST_LOG_TRIVIAL(trace) << "getting `Service` from injector"; \
//const std::vector<TaskService *> &services = injector.getMultibindings<TaskService>(); \
//BOOST_LOG_TRIVIAL(trace) << "creating thread pool with size " << services.size(); \
//boost::asio::thread_pool pool(services.size()); \
//for (const auto &service: services) { \
//BOOST_LOG_TRIVIAL(trace) << "posting service to thread pool"; \
//boost::asio::post(pool, [&service] {                                 \
//service->setup();                                                      \
//BOOST_LOG_TRIVIAL(trace) << "service runner finished"; \
//}); \
//}\
//BOOST_LOG_TRIVIAL(trace) << "joining pool threads"; \
//pool.join();                                                         \
//BOOST_LOG_TRIVIAL(trace) << "thread pool finished"; \
//return -1; \
//}\


#endif //ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
