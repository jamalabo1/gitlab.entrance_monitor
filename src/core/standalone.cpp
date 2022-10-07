//
// Created by root on 9/29/22.
//
#include <core/standalone.h>
#include <core/cancellation_token.h>
#include <boost/thread.hpp>

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
void core::runner(fruit::Injector<IoContext>& injector) {
    BOOST_LOG_TRIVIAL(info) << "initiation service runner";
    core::init_service_runner();
    BOOST_LOG_TRIVIAL(info) << "Running as standalone";
    auto io_context = injector.get<shared_ptr<core::IoContext>>();
    BOOST_LOG_TRIVIAL(trace) << "getting `Service`(s) from injector";
    const std::vector<core::Service *> &services = injector.getMultibindings<core::Service>();
    core::run_services(io_context, services);
}

int core::run_services(shared_ptr<core::IoContext> io_context, const std::vector<core::Service *> &services) {
    auto post = [&]( std::function<void()>&& func) {
        boost::asio::post(GET_BOOST_IO_CONTEXT(io_context), [func](){
            func();
        });
    };

    for (const auto &service: services) {
        post([&post, &io_context, service]() {
            // setup service to register tasks.
             service->setup();

            // get registered tasks.
            auto tasks = service->getTasks();

            // loop over tasks
            for (const auto &task: tasks) {

                // post each task to the io_context.
                post([&io_context, task]() {
                    // subscribe sub-token to the main token.
                    auto token = make_shared<CancellationToken>();

                    // configure the task.
                    bool result = task->configure();

                    if(!result) {
                        // TODO: handle the failing of the task (e.g., re-schedule executing (retry-policy)).
                    }

                    // get runtime options for the task.
                    auto options = task->setup(io_context, token);

                    // execute the task, this call must be blocking or non-dependent on options
                    // because they are freed after the execution complete.
                    // only `task` lives.
                    options.executor([task] {
                            task->operator()();
                    });

                    BOOST_LOG_TRIVIAL(trace)<< "execution of task: " << typeid(task).name()  << " has completed";
                });
            }
        });
    }

    boost::thread_group pool;
    auto hc = boost::thread::hardware_concurrency();

    BOOST_LOG_TRIVIAL(trace) << "device hardware concurrency: " << hc;

    for (auto i = 0u; i<hc; ++i)
        pool.create_thread([&] {io_context->run(); });

    BOOST_LOG_TRIVIAL(debug) << "joining all threads for io_context.";
    pool.join_all();
    BOOST_LOG_TRIVIAL(debug) << "threads finished joining.";

    return -1;
}