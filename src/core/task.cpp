//
// Created by jamal on 28/09/2022.
//

#include <core/task.h>

#include <utility>

namespace core {

    health::Status Task::health_check() const {
        return health::Status::Ok;
    }

    Task::RunOptions Task::setup(shared_ptr<IoContext> ctx, shared_ptr<CancellationToken> token) {
        token_ = std::move(token);
        auto default_executor = [&](const RunOptions::ExecutorCallback &cb) {
            // the default execution strategy is to loop until the operation is requested to cancel.
            while (token_->isActive()) {
                cb();
            }
        };
        return {
                default_executor
        };
    }

    bool Task::configure() {
        // default configure is true. (no configurations needed).
        return true;
    }

    std::string Task::name() const {
        return typeid(this).name();
    }
}
