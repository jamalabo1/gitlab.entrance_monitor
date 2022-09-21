//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_MSGPACKER_H
#define ENTRANCE_MONITOR_V2_MSGPACKER_H

#include <system_error>
#include <unordered_map>
#include <msgpack/msgpack.hpp>

#include <core/communication/consume/consumer_message.h>

#include <utils/string_utils.h>

#include <view_models/frame_view.h>
#include <opencv2/core/mat.hpp>

namespace core::msgpacker {


    template<class T>
    T unpack(const std::vector<uint8_t> &data) {
        return msgpack::unpack<T>(data);
    }

    template<class T>
    T unpack(const std::string &data) {
        const std::vector<uint8_t> vector = string_to_vector(data);
        return unpack<T>(vector);
    }

    template<class T>
    T unpack(const core::communication::consume::ConsumerMessage::ptr_t &message) {
        return unpack<T>(message->Body());
    }

    template<class T>
    std::vector<uint8_t> pack(T data) {
        return msgpack::pack(data);
    }


    cv::Mat unpack_frame_mat(const std::string &);

    cv::Mat unpack_frame_mat(const FrameView &);

    FrameView unpack_frame(const std::string &);
}


#endif //ENTRANCE_MONITOR_V2_MSGPACKER_H
