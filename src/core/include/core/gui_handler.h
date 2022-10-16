//
// Created by jamal on 14/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_GUI_HANDLER_H
#define ENTRANCE_MONITOR_V2_GUI_HANDLER_H

#include <core/init.h>

#include <queue>
#include <mutex>
#include <utility>

#include <opencv2/core/mat.hpp>

namespace core {


    struct IFrame {
        std::string name;
        cv::Mat frame;
    };

    class GUIQueue {
    private:
        std::mutex lock;
        std::queue<IFrame> _queue;
    public:
        GUIQueue() : _queue() {};

        void push(const IFrame &frame) {
            std::lock_guard g(lock);
            _queue.push(frame);
        }

        IFrame get() {
            // to ensure there is no empty item in the _queue (avoid UB)
            std::lock_guard g(lock);

            IFrame item = _queue.front();
            _queue.pop();
            return item;
        }

        bool empty() {
            return _queue.empty();
        }
    };

    class GUIHandler {
    public:
        virtual void run() = 0;

        virtual void imshow(std::string windowName, cv::Mat &mat) = 0;
    };

    using $GUIHandler = $Exported<core::GUIQueue, core::GUIHandler>;

    using GUIHandlerComponent = $GUIHandler::PureComponent;

    GUIHandlerComponent getGUIHandlerComponent();
}

#endif //ENTRANCE_MONITOR_V2_GUI_HANDLER_H
