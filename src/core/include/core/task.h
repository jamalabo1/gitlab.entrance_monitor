//
// Created by jamal on 28/09/2022.
//
#ifndef ENTRANCE_MONITOR_V2_CORE_TASK_H
#define ENTRANCE_MONITOR_V2_CORE_TASK_H

#include <core/init.h>
#include <core/io_context.h>
#include <core/cancellation_token.h>
#include <core/health.h>
#include <boost/asio.hpp>



#define CORE_DEFINE_TASK_DEFAULT(ServiceName, task_name, ...) \
class task_name : public core::Task {}; \
using $##task_name = $Exported<task_name>; \
using task_name##Component = $##task_name::Component<__VA_ARGS__>; \
task_name##Component get##ServiceName##task_name()


namespace core {

    // task class representing work for service.
    // singleton.
    class Task : public health::ICheckable {
    protected:
        //shared_ptr<IoContext> ctx_;
        /// unique token for the task, but is defined as shared_ptr because it can be shared with multiple threads.
        shared_ptr<core::CancellationToken> token_;
    public:
        /// task result struct
        struct TaskResult {
            /// error code.
            boost::system::error_code err;
        };

        struct RunOptions {
            using ExecutorCallback = std::function<void()>;
            using Executor = std::function<void(ExecutorCallback)>;

            Executor executor;
        };


        // set up the task. this method purpose is to tell the caller how to execute the task
        virtual RunOptions setup(shared_ptr<IoContext>, shared_ptr<core::CancellationToken>);

        // configure the task, this is almost like a constructor job, but it's move here to enable faster object creation
        // so that the DI can create the objects faster (faster startup time).
        // if this function fails, the task is re-scheduled to be executed for later time.
        // it's called before the setup method. so that if it failed, there is no need to set up the task.
        virtual bool configure();

        ///
        /// \return if there is an error occurred in executing the task, it's returned.
        virtual TaskResult operator()() = 0;

        /// health check function for periodic check.
        health::Status health_check() const override;


    };

}
#endif //ENTRANCE_MONITOR_V2_CORE_TASK_H
