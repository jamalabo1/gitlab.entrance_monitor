//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_FRAMEVIEW_H
#define ENTRANCE_MONITOR_V2_FRAMEVIEW_H

#include <core/view.h>
#include <string>
#include <vector>

struct FrameView : core::View {
    FrameView() = default;

    FrameView(std::vector<uint8_t> data, uint64_t timestamp, std::string extension = "jpg") :
            extension(std::move(extension)),
            timestamp(timestamp),
            frame_data(std::move(data)) {}

    uint64_t timestamp;
    std::vector<uint8_t> frame_data;
    std::string extension;

    pack_items(frame_data, timestamp, extension)
};

#endif //ENTRANCE_MONITOR_V2_FRAMEVIEW_H
