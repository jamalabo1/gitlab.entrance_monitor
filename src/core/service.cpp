//
// Created by jamal on 30/08/2022.
//
#include <core/service.h>

using namespace core;

Service::Service(IoRunner *io_runner) : io_runner(io_runner) {
    pool = io_runner->get_pool();
}

int Service::run() {
    io_runner->setup();
    pool->join();
    return -1;
}

void Service::post(std::function<void()> cb) {
    io_runner->post(cb);
}


