//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_INIT_H
#define ENTRANCE_MONITOR_V2_INIT_H

// TODO: flip the include dependency from sub-headers including the core headers to the opposite

#include <fruit/fruit.h>
#include <core/ptrs.h>
#include <core/configurations.h>

#define _RequiredComponents core::Configurations

using RequiredComponents = fruit::Required<_RequiredComponents>;

#define MakeRequiredComponents(...) fruit::Required<_RequiredComponents, __VA_ARGS__>


#define shared_factory(x) std::function<shared_ptr<x>()>
#define unique_factory(x) std::function<unique_ptr<x>()>
#define unique_factory_a(x, r) std::function<unique_ptr<x>(r)>

#define APP_DEBUG !NDEBUG
//#ifndef NDEBUG
//#endif

#endif //ENTRANCE_MONITOR_V2_INIT_H
