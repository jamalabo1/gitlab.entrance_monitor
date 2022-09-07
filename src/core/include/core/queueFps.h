#pragma once

#ifndef CORE_QUEUE_FPS_HPP
#define CORE_QUEUE_FPS_HPP

#include <condition_variable>
#include <mutex>
#include <queue>
#include <opencv2/core.hpp>
#include <core/logging.h>

enum severity_level {
    trace
};

namespace core {

    template<typename T>
    class QueueFPS {

    private:
        std::queue<T> queue;

    public:
        QueueFPS() : queue(), counter(0), c(), logger() {
            logger.add_attribute("QueueName",
                                 boost::log::attributes::constant<std::string>(typeid(this).name())
            );
        }

        void push(const T &entry) {
            BOOST_LOG_TRIVIAL(trace) << "requesting mutex lock";
            std::lock_guard<std::mutex> lock(mutex);
            BOOST_LOG_TRIVIAL(trace) << "pushing into _queue";
            if (queue.size() > 15) {
                clear(true);
            }
            queue.push(entry);

            counter += 1;
            if (counter == 1) {
                // Start counting from a second frame (warmup).
                tm.reset();
                tm.start();
            }
        }

        T get() {
            BOOST_LOG_TRIVIAL(trace) << "waiting for mutex lock";
            std::lock_guard<std::mutex> lock(mutex);
            BOOST_LOG_TRIVIAL(trace) << "receiving item from _queue front";
            T entry = queue.front();
            BOOST_LOG_TRIVIAL(trace) << "popping received item from the _queue";
            queue.pop();
            BOOST_LOG_TRIVIAL(trace) << "returning received item";
            return entry;
        }

        bool empty() {
            return queue.empty();
        }


        float getFPS() {
            tm.stop();
            double fps = counter / tm.getTimeSec();
            tm.start();
            return static_cast<float>(fps);
        }

        void clear(bool locked = false) {
            if (!locked) {

                std::lock_guard<std::mutex> lock(mutex);
            }
            while (!queue.empty())
                queue.pop();
        }

        unsigned int counter;
    private:
        cv::TickMeter tm;
        std::mutex mutex;
        std::condition_variable c;
        boost::log::sources::logger logger;
    };
}

#endif // CORE_QUEUE_FPS_HPP