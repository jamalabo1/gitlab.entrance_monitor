//
// Created by root on 10/5/22.
//

#ifndef ENTRANCE_MONITOR_V2_COMPUTE_BLOCKAGE_TASK_IMPL_H
#define ENTRANCE_MONITOR_V2_COMPUTE_BLOCKAGE_TASK_IMPL_H

#include "tasks/compute_blockage_task.h"

#include <core/communication.h>

namespace blocking_computation::tasks::impl {

    class ComputeBlockageTaskImpl : public ComputeBlockageTask,
                                    public core::communication::consume::ConsumerMessageHandler{
    private:
        shared_ptr<core::communication::consume::Consumer> consumer_;
        unique_ptr<core::communication::consume::ConsumeOptions> consume_options_;

        shared_ptr<core::communication::publish::PublisherFactory> publisher_factory_;
        shared_ptr<core::communication::publish::Publisher> publisher_;
    public:
        INJECT(ComputeBlockageTaskImpl(
                shared_ptr<core::communication::publish::PublisherFactory>,
                shared_ptr<core::communication::consume::Consumer>
        ));

        RunOptions setup(shared_ptr<core::IoContext> ptr, shared_ptr<core::CancellationToken> sharedPtr) override;

        bool configure() override;

        TaskResult operator()() override;

    private:
        void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;

    };

} // impl

#endif //ENTRANCE_MONITOR_V2_COMPUTE_BLOCKAGE_TASK_IMPL_H
