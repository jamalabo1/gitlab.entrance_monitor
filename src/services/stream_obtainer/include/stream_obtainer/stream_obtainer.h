//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H
#define ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H

#include <core/core.h>

namespace stream_obtainer {

    class StreamObtainer : public core::Service {

    public:
        INJECT(StreamObtainer(const std::vector<shared_ptr<core::Task>>& ));

        ~StreamObtainer();
    };

    using $StreamObtainer = $Exported<StreamObtainer>;
    using StreamObtainerComponent = $StreamObtainer::PureComponent;

    StreamObtainerComponent getStreamObtainerComponent();
}


#endif //ENTRANCE_MONITOR_V2_STREAM_OBTAINER_H
