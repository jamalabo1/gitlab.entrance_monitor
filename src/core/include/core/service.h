//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H
#define ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H

#include <boost/asio.hpp>
#include <core/io_runner.h>
#include <core/cancellation_token.h>


/*
 *
 *
 * */
namespace core {

/***
 * tasks service is class for manging services in project_runner, or standalone.
 * */
    class Service {
    protected:
        shared_ptr<boost::asio::thread_pool> pool;
        IoRunner* io_runner;
        CancellationToken token;

        ///
        /// \param io_runner io runner is a class given to the task service to operate tasks on.
        explicit Service(core::IoRunner* io_runner);

    public:

        virtual int setup() = 0;

        virtual int run();

        virtual void post(std::function<void()> cb);
    };

}


#endif //ENTRANCE_MONITOR_V2_CORE_TASK_SERVICE_H
