//
// Created by jamal on 30/08/2022.
//
#include <core/service.h>


void core::Service::registerTask(shared_ptr<core::Task> task) {
    tasks_.emplace(task);
}

void core::Service::registerTasks(std::set<shared_ptr<Task>> &tasks) {
    tasks_.merge(tasks);
}

core::health::Status core::Service::health_check() const  {
    return health::Status::Ok;
}
