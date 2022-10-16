//
// Created by jamal on 19/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_UTILS_MACROS_H
#define ENTRANCE_MONITOR_V2_UTILS_MACROS_H

#ifdef NDEBUG
#define APP_DEBUG false
#endif

// if the build type is debug
#ifndef NDEBUG
// set the app_debug to true
#define APP_DEBUG true
#endif

#endif //ENTRANCE_MONITOR_V2_UTILS_MACROS_H
