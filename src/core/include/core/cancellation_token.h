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
        static bool default_state;

        CancellationToken() {
            token = default_state;
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
    bool CancellationToken::default_state = true;
}

#endif //ENTRANCE_MONITOR_V2_CANCELLATION_TOKEN_H
