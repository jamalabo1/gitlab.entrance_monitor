//
// Created by jamal on 30/08/2022.
//
#include <core/task_service.h>

using namespace core;

TaskService::TaskService(IoRunner *io_runner) :  io_runner(io_runner) {
    pool = io_runner->get_pool();
}

int TaskService::run() {
    io_runner->setup();
    pool->join();
    return -1;
}

void TaskService::post(std::function<void()> cb) {
    io_runner->post(cb);
}


