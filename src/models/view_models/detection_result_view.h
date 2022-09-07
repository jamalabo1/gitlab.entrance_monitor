//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H
#define ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H


#include <utility>
#include <vector>
#include <core/view.h>
#include "frame_view.h"

struct DetectionResultObjectView : core::View {

    FrameView object;
    int8_t confidence;
    int classId;
    // 4 element box
    std::vector<int> box;

    DetectionResultObjectView() = default;

    DetectionResultObjectView(
            FrameView &object,
            int8_t confidence,
            int classId,
            std::vector<int> box
    ) : confidence(confidence), classId(classId), box(std::move(box)), object(object) {}

    pack_items(confidence, classId, box, object)
};

struct DetectionResultView : core::View {

    core::ViewId frameId;
    uint64_t timestamp;
    std::vector<DetectionResultObjectView> objects;
    // 2 element box
    std::vector<int> frame_dimensions;

    DetectionResultView() = default;

    DetectionResultView(
            core::ViewId frameId,
            uint64_t timestamp,
            std::vector<DetectionResultObjectView> objects,
            std::vector<int> frame_dimensions
    ) : objects(std::move(objects)),
        timestamp(timestamp),
        frame_dimensions(std::move(frame_dimensions)), frameId(std::move(frameId)) {}

    pack_items(objects, timestamp, frame_dimensions, frameId)
};


#endif //ENTRANCE_MONITOR_V2_VIEW_MODELS_DETECTION_RESULT_VIEW_H
