//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
#define ENTRANCE_MONITOR_V2_CORE_STANDALONE_H

#include <core/init.h>
#include <core/logging.h>

#include <core/service.h>
#include <core/io_context.h>
#include <boost/stacktrace.hpp>

#include <iostream>

#ifdef WIN32

#include <WinBase.h>

#endif

#define DEFINE_STACK_TRACKED_CALL(Block)  \
try Block \
catch(...) {                                      \
    BOOST_LOG_TRIVIAL(fatal) << "an error has occurred at the application";                   \
    std::cout << boost::stacktrace::stacktrace() << std::endl;                     \
}

#define BUILD_STANDALONE_FROM_SERVICE(component)                                             \
int main() {                                                                                 \
DEFINE_STACK_TRACKED_CALL({ \
BOOST_LOG_TRIVIAL(info) << "creating services injector"; \
fruit::Injector injector(component);                                                         \
core::runner(injector);                                                              \
})\
}

namespace core {
    void runner(fruit::Injector<core::IoContext> &);

    void init_service_runner();

    void run_io_context(shared_ptr<core::IoContext> io_context);

    ///
    /// \param io_context io context for running services on (post)
    /// \param services services which have tasks to be ran
    /// \return -1
    int run_services(shared_ptr<core::IoContext> io_context, const std::vector<core::Service *> &services);
}

#endif //ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
