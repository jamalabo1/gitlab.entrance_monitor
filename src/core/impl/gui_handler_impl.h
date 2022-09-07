//
// Created by jamal on 08/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_GUI_HANDLER_IMPL_H
#define ENTRANCE_MONITOR_V2_GUI_HANDLER_IMPL_H

#if false
#define OPENCV_HAS_GUI false
#endif

#include <core/gui_handler.h>

namespace core::impl {
    class GUIHandlerImpl : public GUIHandler {
    private:
        GUIQueue* m_queue;

    public:
        INJECT(GUIHandlerImpl(GUIQueue*));

        void run() override;

        void imshow(std::string windowName, cv::Mat &mat) override;

    };
}

#endif //ENTRANCE_MONITOR_V2_GUI_HANDLER_IMPL_H
