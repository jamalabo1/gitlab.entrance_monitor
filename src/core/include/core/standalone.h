//
// Created by jamal on 10/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
#define ENTRANCE_MONITOR_V2_CORE_STANDALONE_H

#include <core/init.h>
#include <core/logging.h>

#include <core/service.h>
#include <core/io_context.h>


#ifdef WIN32

#include <WinBase.h>

#endif



namespace core {
    void runner(fruit::Injector<core::IoContext>&);
    void init_service_runner();
    ///
    /// \param io_context io context for running services on (post)
    /// \param services services which have tasks to be ran
    /// \return -1
    int run_services(shared_ptr<core::IoContext> io_context, const std::vector<core::Service *> &services);
}

#define BUILD_STANDALONE_FROM_SERVICE(component)                                             \
int main() {                                                                                 \
BOOST_LOG_TRIVIAL(info) << "creating services injector"; \
std::thread t([&]() {                                                                       \
fruit::Injector injector(component);                                                         \
core::runner(injector);                                                              \
});                                                                                           \
t.join(); \
}
#endif //ENTRANCE_MONITOR_V2_CORE_STANDALONE_H
