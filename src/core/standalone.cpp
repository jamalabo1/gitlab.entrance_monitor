//
// Created by root on 9/29/22.
//
#include <core/standalone.h>

void core::init_service_runner() {
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

int core::run_services(core::IoContext* io_context, const std::vector<core::Service *> &services) {
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

    return -1;
}