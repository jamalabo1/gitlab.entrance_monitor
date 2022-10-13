//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H
#define ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H


#include <utility>
#include <vector>
#include <core/view.h>
#include "frame_view.h"

namespace views {

    struct DetectionResultObjectView : core::View {
        using box_type = std::array<int, 4>;

        FrameView object;
        int8_t confidence;
        int classId;
        // 4 element box
        box_type box;

        DetectionResultObjectView() = default;

        DetectionResultObjectView(
                FrameView &object,
                int8_t confidence,
                int classId,
                std::array<int, 4> box
        ) : confidence(confidence), classId(classId), box(std::move(box)), object(object) {}

        pack_items(confidence, classId, box, object)
    };

    struct DetectionResultView : core::View {
        using dimensions_type = std::array<int, 2>;

        core::ViewId frameId;
        uint64_t timestamp;
        std::vector<DetectionResultObjectView> objects;
        // 2 element box
        dimensions_type frame_dimensions;

        DetectionResultView() = default;

        ~DetectionResultView() = default;

        DetectionResultView(
                core::ViewId frameId,
                uint64_t timestamp,
                std::vector<DetectionResultObjectView> objects,
                dimensions_type frame_dimensions
        ) : objects(std::move(objects)),
            timestamp(timestamp),
            frame_dimensions(std::move(frame_dimensions)), frameId(std::move(frameId)) {}

        pack_items(objects, timestamp, frame_dimensions, frameId)
    };
}


#endif //ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H
