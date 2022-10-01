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



namespace core {
    void init_service_runner();
    ///
    /// \param io_context io context for running services on (post)
    /// \param services services which have tasks to be ran
    /// \return -1
    int run_services(shared_ptr<core::IoContext> io_context, const std::vector<core::Service *> &services);
}

#define BUILD_STANDALONE_FROM_SERVICE(component)                                             \
int main() {                                                                                 \
fruit::Injector injector(component);                                                         \
BOOST_LOG_TRIVIAL(info) << "initiation service runner";                                      \
core::init_service_runner();                                                                 \
BOOST_LOG_TRIVIAL(info) << "Running as standalone";                                          \
auto io_context = injector.get<shared_ptr<core::IoContext>>();                               \
BOOST_LOG_TRIVIAL(trace) << "getting `Service`(s) from injector";                            \
const std::vector<core::Service *> &services = injector.getMultibindings<core::Service>();   \
core::run_services(io_context, services);                                                    \
}


#endif //ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
