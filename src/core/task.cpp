//
// Created by jamal on 28/09/2022.
//

#include <core/task.h>

core::health::Status core::Task::health_check() const {
    return health::Status::Ok;
}
