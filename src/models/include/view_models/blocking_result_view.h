//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKING_RESULT_VIEW_H
#define ENTRANCE_MONITOR_V2_BLOCKING_RESULT_VIEW_H

#include <core/view.h>

namespace views {
    class BlockingResultView : core::View {
    public:
        bool result;
        uint64_t frame_timestamp;

        BlockingResultView() = default;

        BlockingResultView(bool result, uint64_t frame_timestamp) : result(result), frame_timestamp(frame_timestamp) {};


        pack_items(result, frame_timestamp);
    };
}

#endif //ENTRANCE_MONITOR_V2_BLOCKING_RESULT_VIEW_H
