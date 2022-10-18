//
// Created by jamal on 30/08/2022.
//
#include <core/service.h>
#include <utils/types.h>

namespace core {

    void Service::registerTask(shared_ptr<Task> task) {
        tasks_.emplace_back(task);
    }

    void Service::registerTasks(const std::vector<shared_ptr<Task>> &tasks) {
        tasks_ = tasks;
    }

    health::Status Service::health_check() const {
        return health::Status::Ok;
    }

    const std::vector<shared_ptr<Task>> &Service::getTasks() const {
        return tasks_;
    }

    int Service::setup() {
        return 0;
    }

    std::string Service::name() const {
        return utils::type_name(this);
    }

}
