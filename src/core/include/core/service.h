//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H
#define ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H

#include <boost/asio.hpp>
#include <core/io_context.h>
#include <core/cancellation_token.h>
#include <core/health.h>
#include <core/task.h>
#include <set>

/*
 *
 *
 * */
namespace core {

/***
 * tasks service is class for manging services in project_runner, or standalone.
 * */
    class Service : public health::ICheckable {
    private:
        std::vector<shared_ptr<Task>> tasks_;
    protected:
        shared_ptr<IoContext> ctx_;
//        shared_ptr<boost::asio::thread_pool> pool;
//        IoRunner* io_runner;
//        CancellationToken token;

        void registerTask(shared_ptr<Task> task);

        void registerTasks(const std::vector<shared_ptr<Task>> &tasks);

        ///
        /// \param io_runner io runner is a class given to the task service to operate tasks on.
//        explicit Service(core::IoRunner* io_runner);
//        void registerTask(core::Task& task);
    public:

        // setup function, called to coordinate the handling of tasks.
        virtual int setup();

        // default health check.
        health::Status health_check() const override;

        virtual const std::vector<shared_ptr<Task>> &getTasks() const;

        virtual std::string name() const;
    };

}


#endif //ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H
