//
// Created by jamal on 20/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_COMMUNICATION_H
#define ENTRANCE_MONITOR_V2_COMMUNICATION_H

#include <core/init.h>
#include <core/communication/publish.h>
#include <core/communication/consume.h>


namespace core::communication {
    EXPORT_MODULE(getCommunicationComponents, publish::$Components, consume::$Components);
}

#endif //ENTRANCE_MONITOR_V2_COMMUNICATION_H
