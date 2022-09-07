//
// Created by jamal on 25/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_LOGGING_H
#define ENTRANCE_MONITOR_V2_LOGGING_H

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/attributes/constant.hpp>

#include <boost/log/expressions.hpp>

#ifdef WIN32
#include <SDKDDKVer.h>
#endif

//#include <iostream>
//#undef BOOST_LOG_TRIVIAL
//#define BOOST_LOG_TRIVIAL(args) std::cout

#endif //ENTRANCE_MONITOR_V2_LOGGING_H
