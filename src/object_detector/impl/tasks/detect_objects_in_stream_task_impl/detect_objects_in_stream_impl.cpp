//
// Created by root on 10/2/22.
//

#include "detect_objects_in_stream_impl.h"

using namespace core::communication;

object_detector::tasks::detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::DetectObjectsInStreamTaskImpl(shared_ptr<core::communication::consume::Consumer> consumer) : consumer_(consumer)  {

}

core::Task::RunOptions
object_detector::tasks::detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::setup(shared_ptr<core::IoContext> io_context,
                                                                                             shared_ptr<core::CancellationToken> token) {

    // set up the consume options here.
    consume::ConsumeOptions options(
         shared_from_this(),
         token,
         ""
     );
 consume_options_ = options;

return Task::setup(io_context, token);
}

bool object_detector::tasks::detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::configure() {
    return Task::configure();
}

core::Task::TaskResult
object_detector::tasks::detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::operator()() {
    return TaskResult();
}

void object_detector::tasks::detect_objects_in_stream::impl::DetectObjectsInStreamTaskImpl::operator()(
        const consume::ConsumerMessage::ptr_t &envelope) const {


}
