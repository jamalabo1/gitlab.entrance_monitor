//
// Created by jamal on 14/08/2022.
//

#include "gui_handler_impl.h"

#include <opencv2/highgui.hpp>

using namespace core;
using namespace core::impl;


GUIHandlerImpl::GUIHandlerImpl(GUIQueue *queue) : m_queue(queue) {

}

void GUIHandlerImpl::run() {

#ifdef OPENCV_HAS_GUI
    for (;;) {
        if (!m_queue->empty()) {
            IFrame item = m_queue->get();
            cv::namedWindow(item.name);
            cv::imshow(item.name, item.frame);
        }
        cv::waitKey(1);
    }
#endif

}


void GUIHandlerImpl::imshow(std::string windowName, cv::Mat &mat) {
#ifdef OPENCV_HAS_GUI
    IFrame frame{
            std::move(windowName),
            mat
    };
    m_queue->push(frame);
#endif
}

GUIHandlerComponent core::getGUIHandlerComponent() {
    return fruit::createComponent()
            .registerProvider([]() {
                return new GUIQueue();
            })
            .bind<GUIHandler, GUIHandlerImpl>();
}


