//
// Created by jamal on 28/09/2022.
//
#ifndef ENTRANCE_MONITOR_V2_CORE_TASK_H
#define ENTRANCE_MONITOR_V2_CORE_TASK_H

#include <core/init.h>
#include <core/io_context.h>
#include <core/health.h>
#include <boost/asio.hpp>

namespace core {

    // task class representing work for service.
    class Task : public health::ICheckable {
    protected:
        shared_ptr<IoContext> ctx_;

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
        health::Status health_check() const override {
            // defaults to true if not overridden.
            return health::Status::Ok;
        }
    };

}
#endif //ENTRANCE_MONITOR_V2_CORE_TASK_H
