//
// Created by jamal on 13/08/2022.
//
#include "detection_message_handler.h"

#include <core/msgpacker.h>

#include <view_models/blocking_result_view.h>

#include <core/logging.h>
#include <opencv2/opencv.hpp>

#include <boost/asio.hpp>

#include <utils/vector.h>


namespace utils_vector = utils::vector;

using namespace fruit;
using namespace std;
using namespace cv;
using namespace core;
using namespace core::communication::publish;
using namespace core::msgpacker;
using namespace core::communication::consume;


vector<Point> match_to_shape(vector<Point> &pts, Size original_shape, Size shape);

bool compareContourAreas(const std::vector<cv::Point> &contour1, const std::vector<cv::Point> &contour2);

DetectionMessageHandler::DetectionMessageHandler(PublisherFactory *publisher_factory, core::GUIHandler *gui_handler)
        : gui_handler(gui_handler) {
    publisher = publisher_factory->create_publisher("blocking.{1}");
}

void DetectionMessageHandler::operator()(const ConsumerMessage::ptr_t &envelope) const {
    static auto original_shape = Size(1920, 1080);
    static auto bounding_points = vector<Point>{
            Point(1920, 650),
            Point(826, 1080),
            Point(573, 700),
            Point(1114, 508),
            Point(1403, 476),
    };
    auto detectionResultView = core::msgpacker::unpack<DetectionResultView>(envelope);


    BOOST_LOG_TRIVIAL(trace) << "received detection result with " << detectionResultView.objects.size()
                             << " objects and frame-width: " << detectionResultView.frame_dimensions[0];


    boost::asio::thread_pool pool(detectionResultView.objects.size());

    auto frame_dimension = Size(detectionResultView.frame_dimensions[0], detectionResultView.frame_dimensions[1]);

    auto relative_points = match_to_shape(bounding_points, original_shape, frame_dimension);


    std::atomic_int results_count = 0;


    for (const auto &obj: detectionResultView.objects) {
        //obj, &frame_dimension, &results_count, &relative_points
        boost::asio::post(pool, [&]() {
            auto result = compute_intersection(obj, frame_dimension, relative_points);
            if (result.has_value() && result.get()) {
                results_count++;
            }
        });
    }

    pool.join();

    BlockingResultView blockingResult(results_count > 0, detectionResultView.timestamp);

    publisher->publish(blockingResult);
}

boost::optional<bool>
DetectionMessageHandler::compute_intersection(const DetectionResultObjectView &detection_result_object, Size &frameDimension,
                     vector<Point> &boundingPoints) const {
    static auto kernel_size = Size(3, 3);

    if(detection_result_object.confidence < 80) return {};

    Mat object = unpack_frame_mat(detection_result_object.object);


    Mat gray;
    cvtColor(object, gray, COLOR_BGR2GRAY);

    Mat object_mask = Mat::zeros(frameDimension, CV_8UC1);

    cv::Rect roi(cv::Point(detection_result_object.box[0], detection_result_object.box[1]), gray.size());
    gray.copyTo(object_mask(roi));


    Mat blurred;
    GaussianBlur(object_mask, blurred, ref(kernel_size), 0);

    Mat thresh;
    threshold(
            blurred,
            thresh,
            0,
            255,
            THRESH_BINARY | THRESH_OTSU
    );

    std::vector<std::vector<cv::Point> > contours;

    findContours(thresh, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
    if (contours.empty()) return {};
    std::sort(contours.begin(), contours.end(), compareContourAreas);

    // take the largest contour only
    contours.resize(1);
//    contours.emplace_back(
//            boundingPoints
//    );

    Mat mask_1 = Mat::zeros(frameDimension, CV_8UC1);
    Mat mask_2 = Mat::zeros(frameDimension, CV_8UC1);

    drawContours(
            mask_1,
            contours,
            0,
            255
    );
    fillPoly(
            mask_2,
            boundingPoints,
            255
    );


    Mat intersection_mask;

    bitwise_and(mask_1, mask_2, intersection_mask);

#ifdef APP_DEBUG
    gui_handler->imshow("mask_1", mask_1);
    gui_handler->imshow("mask_2", mask_2);
    gui_handler->imshow("intersection_mask", intersection_mask);
#endif

    int intersection_sum = countNonZero(intersection_mask);
    return intersection_sum > 10;
}

vector<Point> match_to_shape(vector<Point> &pts, Size original_shape, Size shape) {
    float w_factor = shape.width / float(original_shape.width);
    float h_factor = shape.height / float(original_shape.height);


    return utils_vector::transform<Point, Point>(pts, [w_factor, h_factor](Point &p) {
        return Point(p.x * w_factor, p.y * h_factor);
    });
}

// comparison function object
bool compareContourAreas(const std::vector<cv::Point> &contour1, const std::vector<cv::Point> &contour2) {
    double a = fabs(contourArea(contour1));
    double b = fabs(contourArea(contour2));
    return (a > b);
}

DetectionMessageHandlerComponent getDetectionMessageHandlerComponent() {
    return createComponent()
            .install(getCommunicationPublishComponents)
            .bind<ConsumerMessageHandler, DetectionMessageHandler>();
}