//
// Created by jamal on 15/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_IMPL_H
#define ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_IMPL_H

#ifdef WIN32
#include "win32/sound_controller_win32_impl.h"
#else

#include "linux/sound_controller_linux_impl.h"

#endif

#endif //ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_IMPL_H
