//
// Created by jamal on 29/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_SUBSCRIBE_TO_STREAM_TASK_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_SUBSCRIBE_TO_STREAM_TASK_H

#include <core/init.h>
#include <core/cancellation_token.h>
#include <core/task.h>

namespace stream_obtainer::tasks {

class SubscribeToStreamTask : public core::Task {


};

using $SubscribeToStreamTask = $Exported<SubscribeToStreamTask>;
using SubscribeToStreamTaskComponent = $SubscribeToStreamTask::PureComponent;

SubscribeToStreamTaskComponent getStreamObtainerSubscribeToStreamTask();

}

#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_INTERFACES_TASKS_SUBSCRIBE_TO_STREAM_TASK_H
