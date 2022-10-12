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



    boost::log::core::get()->set_filter
            (
                    boost::log::trivial::severity >=
#if APP_DEBUG
                    boost::log::trivial::trace
#else
                    boost::log::trivial::info
#endif
                    );


}


void core::runner(fruit::Injector<IoContext>& injector) {
    BOOST_LOG_TRIVIAL(info) << "initiation service runner";
    core::init_service_runner();
    BOOST_LOG_TRIVIAL(info) << "Running as standalone";
    auto io_context = injector.get<shared_ptr<core::IoContext>>();
    BOOST_LOG_TRIVIAL(trace) << "getting `Service`(s) from injector";
    const std::vector<core::Service *> &services = injector.getMultibindings<core::Service>();
    core::run_services(io_context, services);
    BOOST_LOG_TRIVIAL(info) << "finished running standalone service";
}

int core::run_services(shared_ptr<core::IoContext> io_context, const std::vector<core::Service *> &services) {

    auto post = [&]( std::function<void()>&& func) {
        boost::asio::post(GET_BOOST_IO_CONTEXT(io_context), [func](){
            DEFINE_STACK_TRACKED_CALL({
                                          func();
                                      })
        });
    };

    for (const auto &service: services) {
        post([&post, &io_context, service]() {
            BOOST_LOG_TRIVIAL(debug) << "setting up service: " << typeid(service).name();
            // setup service to register tasks.
            service->setup();

            // get registered tasks.
            auto tasks = service->getTasks();

            BOOST_LOG_TRIVIAL(debug) << "looping over service tasks";
            // loop over tasks
            for (const auto &task: tasks) {

                // post each task to the io_context.
                post([&io_context, task]() {
                    auto task_name = typeid(*task).name();

        // subscribe sub-token to the main token.
        auto token = make_shared<CancellationToken>();

        BOOST_LOG_TRIVIAL(debug) << "configuring task: " << task_name;
        // configure the task.
        bool result = task->configure();
        BOOST_LOG_TRIVIAL(debug) << "task (" << task_name <<  ") configure returned : " << result;

        if(!result) {
            // TODO: handle the failing of the task (e.g., re-schedule executing (retry-policy)).
        }

        BOOST_LOG_TRIVIAL(debug) << "setting-up task: " << task_name;
        // get runtime options for the task.
        auto options = task->setup(io_context, token);

        BOOST_LOG_TRIVIAL(debug) << "calling task (" << task_name << ") executor";
        // execute the task, this call must be blocking or non-dependent on options
        // because they are freed after the execution complete.
        // only `task` lives.
        options.executor([task, task_name] {
           //BOOST_LOG_TRIVIAL(info) << "is task " << task_name << " empty? == " << (task.get() == nullptr);
            task->operator()();
        });

                    BOOST_LOG_TRIVIAL(trace)<< "execution of task: " << task_name  << " has completed";
                });
            }
        });
    }

    boost::thread_group pool;
    auto hc = boost::thread::hardware_concurrency();

    BOOST_LOG_TRIVIAL(trace) << "device hardware concurrency: " << hc;

    for (auto i = 0u; i<hc; ++i)
        pool.create_thread([&] { io_context->run(); });

    BOOST_LOG_TRIVIAL(debug) << "joining all threads (" << hc << ") for io_context.";
    pool.join_all();
    BOOST_LOG_TRIVIAL(debug) << "threads finished joining at ";

    return -1;
}