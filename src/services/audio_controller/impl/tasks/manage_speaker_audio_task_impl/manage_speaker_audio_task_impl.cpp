//
// Created by root on 10/12/22.
//

#include "manage_speaker_audio_task_impl.h"

#include <core/logging.h>
#include <core/msgpacker.h>

#include <view_models/blocking_result_view.pb.h>

namespace audio_controller::tasks {

    namespace impl {

        using namespace core::communication::consume;
        using core::msgpacker::pb::unpack;

        using core::amqp::ArgsTable;

        using views::BlockingResultView;

        ManageSpeakerAudioTaskImpl::ManageSpeakerAudioTaskImpl(
                shared_ptr<Consumer> consumer,
                shared_ptr<SoundController> sound_controller) : consumer_(consumer),
                                                                sound_controller_(sound_controller),
                                                                consume_options_(nullptr) {


        }


        core::Task::RunOptions
        ManageSpeakerAudioTaskImpl::setup(shared_ptr<core::IoContext> ctx, shared_ptr<core::CancellationToken> token) {

            // set up the consume options here.
            consume_options_ = make_unique<ConsumeOptions>(
                    this,
                    token,
                    "results.{1}"
            );

            return CORE_TASK_RUN_OPTIONS_ONE_TIME;
        }

        core::Task::TaskResult ManageSpeakerAudioTaskImpl::operator()() {
            consumer_->consume(*consume_options_);
            return TaskResult{};

        }

        void ManageSpeakerAudioTaskImpl::operator()(
                const ConsumerMessage::ptr_t &envelope) const {
            auto view = unpack<BlockingResultView>(envelope);

            BOOST_LOG_TRIVIAL(debug) << "blocking result message was received with result: " << view.result();
            // is blocking
            if (view.result()) {
                sound_controller_->play();
            } else {
                sound_controller_->stop();
            }
        }
    }

    using core::communication::consume::getCommunicationConsumeComponents;

    ManageSpeakerAudioTaskComponent getAudioControllerManageSpeakerAudioTask() {
        return CORE_TASK_CREATE_COMPONENT(ManageSpeakerAudioTask)
                .install(getSoundControllerComponent)
                .install(getCommunicationConsumeComponents);
    }

}
