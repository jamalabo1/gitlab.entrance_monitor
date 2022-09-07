//
// Created by jamal on 10/08/2022.
//

#include "object_detector_impl.h"

#include <core/logging.h>

#include "detection_result.h"
#include "download_file.h"

#include "is_cuda_available.h"

//#include <opencv2/opencv.hpp>

using namespace fruit;
using namespace std;
using namespace cv;
using namespace dnn;

DetectorImpl::DetectorImpl(core::Configurations *configurations, core::IoRunner *io_runner) : configs(configurations) {
    BOOST_LOG_TRIVIAL(trace) << "initiating model preparation";
    io_runner->post([&]() {
        prepare_model();
    });
}

DetectionResult DetectorImpl::detect_objects(const Mat &frame) {
    BOOST_LOG_TRIVIAL(trace) << "locking `detection_model` mutex";
    detection_model_mutex.lock();

    BOOST_LOG_TRIVIAL(trace) << "setting `detection_model` input params";
    detection_model->setInputParams(1.0 / 255.0, Size(416, 416), Scalar(), true);


    vector<int> classIds;
    vector<Rect> boxes;
    vector<float> confidences;

    BOOST_LOG_TRIVIAL(trace) << "detecting objects in `frame`";
    detection_model->detect(frame,
                            classIds,
                            confidences,
                            boxes,
                            0.6,
                            0.4
    );
    BOOST_LOG_TRIVIAL(trace) << "unlocking `detection_model` mutex";
    detection_model_mutex.unlock();

    return {classIds, boxes, confidences};
}

void DetectorImpl::prepare_model() {
    detection_model_mutex.lock();
    BOOST_LOG_TRIVIAL(debug) << "initialing dnn::net reading from darknet";

    auto cfgFile = download_file_from_url(configs->get("dnn-cfgFile"));

    auto weightsFile = download_file_from_url(configs->get("dnn-weightsFile"));

    Net net = readNetFromDarknet(
            cfgFile,
            weightsFile
    );

    // check if cuda is available, if so enable DNN with cuda.
    if (object_detector::utils::is_cuda_available()) {
        BOOST_LOG_TRIVIAL(trace) << "setting dnn::net preferable backend & target";
        net.setPreferableBackend(DNN_BACKEND_CUDA);
        net.setPreferableTarget(DNN_TARGET_CUDA_FP16);
    }

    BOOST_LOG_TRIVIAL(trace) << "creating detection model from net";
    detection_model = make_shared<DetectionModel>(net);
    BOOST_LOG_TRIVIAL(trace) << "unlocking detection model mutex";
    detection_model_mutex.unlock();
}


DetectorComponent getDetectorComponent() {
    return createComponent()
            .bind<Detector, DetectorImpl>();
}
