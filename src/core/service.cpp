//
// Created by jamal on 30/08/2022.
//
#include <core/service.h>


void core::Service::registerTask(shared_ptr<core::Task> task) {
    tasks_.emplace_back(task);
}

void core::Service::registerTasks(std::vector<shared_ptr<Task>> &tasks) {
//    tasks_.(tasks);
}

core::health::Status core::Service::health_check() const  {
    return health::Status::Ok;
}

const std::vector<shared_ptr<core::Task>> &core::Service::getTasks() const {
    return tasks_;
}
