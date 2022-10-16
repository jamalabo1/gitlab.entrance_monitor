//
// Created by jamal on 10/08/2022.
//

#include "object_detector_impl.h"

#include <core/logging.h>

#include "download_file.h"

#include "is_cuda_available.h"


namespace object_detector {

    using fruit::createComponent;

    namespace impl {

        using std::vector;

        using cv::Mat;
        using cv::Rect;
        using cv::Scalar;
        using cv::Size;

        using cv::dnn::Net;
        using cv::dnn::DetectionModel;
        using cv::dnn::readNetFromDarknet;

        using utils::is_cuda_available;
        using utils::download_file_from_url;


        DetectorImpl::DetectorImpl(core::Configurations *configurations) : configs(configurations) {
            BOOST_LOG_TRIVIAL(trace) << "initiating model preparation";
            // let the `prepare_model` sync,
            // so that if the preparation model failed while loading the modules it's not continued.
            prepare_model();
        }

        DetectionResult DetectorImpl::detect_objects(const Mat &frame) {
            BOOST_LOG_TRIVIAL(trace) << "setting `detectionModel_` input params";
            detectionModel_->setInputParams(1.0 / 255.0, Size(416, 416), Scalar(), true);


            vector<int> classIds;
            vector<Rect> boxes;
            vector<float> confidences;

            BOOST_LOG_TRIVIAL(trace) << "detecting objects in `frame`";
            detectionModel_->detect(frame,
                                    classIds,
                                    confidences,
                                    boxes,
                                    0.6,
                                    0.4
            );

            return {classIds, boxes, confidences};
        }

        void DetectorImpl::prepare_model() {
            BOOST_LOG_TRIVIAL(debug) << "initialing dnn::net reading from darknet";

            auto cfgFile = download_file_from_url(configs->get("dnn-cfgFile"));

            auto weightsFile = download_file_from_url(configs->get("dnn-weightsFile"));

            Net net = readNetFromDarknet(
                    cfgFile,
                    weightsFile
            );

            // check if cuda is available, if so enable DNN with cuda.
            if (is_cuda_available()) {
                BOOST_LOG_TRIVIAL(trace) << "setting dnn::net preferable backend & target";
                net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
                net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
            }

            BOOST_LOG_TRIVIAL(trace) << "creating detection model from net";
            detectionModel_ = make_unique<DetectionModel>(net);
        }
    }


    DetectorComponent getDetectorComponent() {
        return createComponent()
                .bind<Detector, impl::DetectorImpl>();
    }

}
