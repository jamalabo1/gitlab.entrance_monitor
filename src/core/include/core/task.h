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
        shared_ptr<IoContext> ctx_;
        /// unique token for the task, but is defined as shared_ptr because it can be shared with multiple threads.
        shared_ptr<core::CancellationToken> token_;
    public:
        /// task result struct
        struct TaskResult {
            /// error code.
            boost::system::error_code err;
        };

        ///
        /// \return if there is an error occurred in executing the task, it's returned.
        virtual TaskResult operator()() = 0;

        /// health check function for periodic check.
        health::Status health_check() const override;

        template<typename CompletionToken>
        BOOST_ASIO_INITFN_RESULT_TYPE(CompletionToken, void()) post(BOOST_ASIO_MOVE_ARG(CompletionToken) token) {
            return boost::asio::post(GET_BOOST_IO_CONTEXT(ctx_), token);
        }
    };

}
#endif //ENTRANCE_MONITOR_V2_CORE_TASK_H
