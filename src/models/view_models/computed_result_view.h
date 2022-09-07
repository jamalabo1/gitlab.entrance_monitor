//
// Created by jamal on 14/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_COMPUTED_RESULT_VIEW_H
#define ENTRANCE_MONITOR_V2_COMPUTED_RESULT_VIEW_H

#include <core/view.h>

class ComputedResultView : public core::View {

public:
//    core::ViewId objectId;

    bool isBlocking;

    ComputedResultView() = default;

    explicit ComputedResultView(bool isBlocking) : isBlocking(isBlocking) {}


    pack_items(isBlocking)
};

#endif //ENTRANCE_MONITOR_V2_COMPUTED_RESULT_VIEW_H
