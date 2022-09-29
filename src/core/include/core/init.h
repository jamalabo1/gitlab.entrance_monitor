// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_INIT_H
#define ENTRANCE_MONITOR_V2_INIT_H

#include <utils/macros.h>
#include <fruit/fruit.h>
#include <core/ptrs.h>
#include <core/configurations.h>

#include <boost/mp11.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>


#define mergeTypelist(...) boost::mp11::mp_append<__VA_ARGS__>
//#define replaceFromTypelist(T, ...) boost::mp11::mp_unique<boost::mp11::mp_rename<mergeTypelist(__VA_ARGS__), T>>
#define replaceFromTypelist(T, ...) boost::mp11::mp_rename<mergeTypelist(__VA_ARGS__), T>
#define componentFromTypelist(...) replaceFromTypelist(fruit::Component, __VA_ARGS__)

#define typelist boost::mp11::mp_list

class IExported {
};


#define _RequiredComponents core::Configurations

using RequiredComponents = fruit::Required<_RequiredComponents>;


#define MakeComponentWithRequired(_Required, ...) fruit::Component<_Required, __VA_ARGS__>
#define MakeRequiredComponents(...) fruit::Required<_RequiredComponents, __VA_ARGS__>
#define MakeCoreComponentWithRequired(_Required, ...) MakeComponentWithRequired(MakeRequiredComponents(_Required), __VA_ARGS__)
#define MakeCoreComponent(...) MakeComponentWithRequired(RequiredComponents, __VA_ARGS__)


#define TYPENAMES_CLS(r, token, i, elm) BOOST_PP_COMMA_IF(i) elm::Typenames
#define WRAP_IEXPORTED(...) BOOST_PP_SEQ_FOR_EACH_I(TYPENAMES_CLS, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


// create required components from typelist
#define MakeRequiredComponentsFromTypeList(...) typelist<replaceFromTypelist(fruit::Required, typelist<_RequiredComponents>, __VA_ARGS__)>


// export a IExported to be used as a required component.
#define ExportRequiredComponents(...) MakeRequiredComponentsFromTypeList(WRAP_IEXPORTED(__VA_ARGS__))


// defines a component from typeList with custom required components
#define MakeComponentFromTypeListWithRequired(required, ...) componentFromTypelist(required, __VA_ARGS__)

// defines a component from typeList
#define MakeComponentFromTypeList(...) MakeComponentFromTypeListWithRequired(typelist<RequiredComponents>, __VA_ARGS__)

// Export a core component with custom required.
#define ExportCoreComponentWithRequired(required, ...) MakeComponentFromTypeListWithRequired(required, WRAP_IEXPORTED(__VA_ARGS__))

// Export a core component that is wrapped with $Export or $Module, or any class with ::Typenames (typelist);
#define ExportCoreComponent(...) MakeComponentFromTypeList(WRAP_IEXPORTED(__VA_ARGS__))


template<typename... T>
class $typelist {
public:
    using Typenames = typelist<T...>;
};

// exported class is a container/wrapper/holder for pack expansion to export types.
template<typename...Ts>
class $Exported : public IExported {
public:
    using Typenames = typelist<Ts...>;

    template<class... TR>
    using Component = MakeComponentFromTypeListWithRequired(MakeRequiredComponentsFromTypeList(typename $typelist<TR...>::Typenames), Typenames);

    using PureComponent = Component<>;
};

template<typename... $TE>
class $Module : public IExported {
public:
    using Typenames = mergeTypelist(typename $TE::Typenames...);
};


#define EXPORT_MODULE(funcName, ...)     using $Components = $Module<__VA_ARGS__>; \
using Components = ExportCoreComponent($Components); \
Components funcName()


#define EXPORT_TASKS_MODULE(funcName, ...)          \
using $Tasks = $Exported<std::vector<core::Task*>>; \
EXPORT_MODULE(getStreamObtainerTasks, $Tasks, __VA_ARGS__)

#define shared_factory(x) std::function<shared_ptr<x>()>
#define unique_factory(x) std::function<unique_ptr<x>()>
#define unique_factory_p(x, ...) std::function<unique_ptr<x>(__VA_ARGS__)>
#define MakeUniqueFactoryP(x, ...) unique_factory_p(x, __VA_ARGS__)
// if the build type is not debug then set app_debug to false

//#ifndef NDEBUG
//#endif

#endif //ENTRANCE_MONITOR_V2_INIT_H
