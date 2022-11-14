//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_MSGPACKER_H
#define ENTRANCE_MONITOR_V2_MSGPACKER_H

#include <system_error>
#include <unordered_map>
#include <msgpack/msgpack.hpp>
#include <opencv2/core/mat.hpp>

#include <core/communication/consume/consumer_message.h>

#include <utils/vector.h>
#include <utils/string_utils.h>

//#include <view_models/frame_view.h>
#include <view_models/frame_view.pb.h>


namespace core::msgpacker {

    namespace pb {
        using utils::vector::vector_to_string;

        template<class T>
        T unpack(const std::string &data) {
            T instance;
            instance.ParseFromString(data);
            return instance;
        }

        template<class T>
        T unpack(const std::vector<uint8_t> &data) {
            return unpack<T>(vector_to_string(data));
        }

        template<class T>
        T unpack(const core::communication::consume::ConsumerMessage::ptr_t &message) {
            return unpack<T>(message->Body());
        }
    }

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

    cv::Mat unpack_frame_mat(const views::FrameView &);
//    cv::Mat unpack_frame_mat(const views::FrameView &);

    views::FrameView unpack_frame(const std::string &);
}


#endif //ENTRANCE_MONITOR_V2_MSGPACKER_H
