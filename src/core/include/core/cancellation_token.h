//
// Created by jamal on 31/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CANCELLATION_TOKEN_H
#define ENTRANCE_MONITOR_V2_CANCELLATION_TOKEN_H

#include <atomic>

namespace core {

    class CancellationToken {
    private:
        std::atomic_bool token;

    public:
        CancellationToken() {
            token = true;
        }

        void cancel() {
            token = false;
        }

        bool isCanceled() const {
            return !token;
        }

        bool isActive() const {
            return token;
        }
    };
}

#endif //ENTRANCE_MONITOR_V2_CANCELLATION_TOKEN_H
