//
// Created by root on 10/12/22.
//

#ifndef ENTRANCE_MONITOR_V2_MANAGE_SPEAKER_AUDIO_TASK_IMPL_H
#define ENTRANCE_MONITOR_V2_MANAGE_SPEAKER_AUDIO_TASK_IMPL_H

#include "tasks/manage_speaker_audio_task.h"

#include <core/communication/consume.h>

#include "sound_controller.h"

namespace audio_controller::tasks::impl {
    class ManageSpeakerAudioTaskImpl :
            public ManageSpeakerAudioTask,
            public core::communication::consume::ConsumerMessageHandler {
    private:
        shared_ptr<core::communication::consume::Consumer> consumer_;
        unique_ptr<core::communication::consume::ConsumeOptions> consume_options_;

        shared_ptr<SoundController> sound_controller_;
    public:
        INJECT(
                ManageSpeakerAudioTaskImpl(
                        shared_ptr<core::communication::consume::Consumer>,
                        shared_ptr<SoundController>
                )
        );

        RunOptions setup(shared_ptr<core::IoContext>, shared_ptr<core::CancellationToken>) override;

        TaskResult operator()() override;

        void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;
    };
}

#endif //ENTRANCE_MONITOR_V2_MANAGE_SPEAKER_AUDIO_TASK_IMPL_H
