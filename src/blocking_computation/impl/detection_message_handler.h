//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_DETECTION_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_DETECTION_MESSAGE_HANDLER_H

#include <core/init.h>

#include <boost/optional.hpp>

#include <core/consumer_message_handler.h>

#include <core/publisher_factory.h>

#include <core/gui_handler.h>

#include <view_models/detection_result_view.h>

class DetectionMessageHandler : public core::consume::ConsumerMessageHandler {

private:
    unique_ptr<core::publish::Publisher> publisher;
    core::GUIHandler *gui_handler;

    boost::optional<bool>

    compute_intersection(const DetectionResultObjectView &detection_result_object, cv::Size &frameDimension,
                         std::vector<cv::Point> &boundingPoints) const;

public:

    INJECT(DetectionMessageHandler(core::publish::PublisherFactory * publisher, core::GUIHandler * gui_handler));

    void operator()(const core::consume::ConsumerMessage::ptr_t &envelope) const override;
};

using DetectionMessageHandlerComponent = fruit::Component<MakeRequiredComponents(
        core::GUIHandler), core::consume::ConsumerMessageHandler>;

DetectionMessageHandlerComponent getDetectionMessageHandlerComponent();

#endif //ENTRANCE_MONITOR_V2_DETECTION_MESSAGE_HANDLER_H
