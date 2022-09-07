//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_TASKSERVICE_H
#define ENTRANCE_MONITOR_V2_TASKSERVICE_H

#include <boost/asio.hpp>
#include <core/io_runner.h>
#include <core/cancellation_token.h>

#define CORE_SERVICE_THREADS 10

namespace core {

/***
 * task service is class for manging services in project_runner, or standalone.
 * */
    class TaskService {
    protected:
        shared_ptr<boost::asio::thread_pool> pool;
        IoRunner* io_runner;
        CancellationToken token;

        explicit TaskService(core::IoRunner* io_runner);

    public:

        virtual int setup() = 0;

        virtual int run();

        virtual void post(std::function<void()> cb);
    };

}


#endif //ENTRANCE_MONITOR_V2_TASKSERVICE_H
