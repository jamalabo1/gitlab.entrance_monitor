// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_INIT_H
#define ENTRANCE_MONITOR_V2_INIT_H

#include <utils/macros.h>
#include <fruit/fruit.h>
#include <core/ptrs.h>
#include <core/configurations.h>

#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/mp11.hpp>


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
#define WRAP_IEXPORTED(...) BOOST_PP_SEQ_FOR_EACH_I(TYPENAMES_CLS,, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))


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
    using Component = MakeComponentFromTypeListWithRequired(
            MakeRequiredComponentsFromTypeList(typename $typelist<TR...>::Typenames), Typenames);

    using PureComponent = Component<>;
};

template<typename... $TE>
class $Module : public IExported {
public:
    using Typenames = mergeTypelist(typename $TE::Typenames...);
};


//#define EXPORT_DEPENDANT_MODULE(required, funcName, ...) ExportCoreComponentWithRequired(required, $typelist<>)
#define EXPORT_DEPENDANT_MODULE(required, funcName, ...) \
using $Components = $Module<__VA_ARGS__>; \
using Components = MakeComponentFromTypeListWithRequired(required, $Components::Typenames); \
Components funcName()

#define EXPORT_MODULE(funcName, ...) EXPORT_DEPENDANT_MODULE(MakeRequiredComponentsFromTypeList(typelist<>), funcName, __VA_ARGS__)


#define EXPORT_TASKS_MODULE(funcName, ...)          \
using $Tasks = $Exported<std::vector<shared_ptr<core::Task>>>; \
EXPORT_MODULE(funcName, $Tasks, __VA_ARGS__)

#define TASKS_PROVIDER_ARG_NAME_(r, token, i, elm) t##i
#define TASKS_PROVIDER_PARAM_NAME(r, token, i, elm)  BOOST_PP_COMMA_IF(i) shared_ptr<elm> TASKS_PROVIDER_ARG_NAME_(r, token, i, elm)
#define TASKS_PROVIDER_PARAMS(...) BOOST_PP_SEQ_FOR_EACH_I(TASKS_PROVIDER_PARAM_NAME, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define TASKS_PROVIDER_ARG_NAME(r, token, i, elm) BOOST_PP_COMMA_IF(i) TASKS_PROVIDER_ARG_NAME_(r, token, i, elm)
#define TASKS_PROVIDER_ARGS(...) BOOST_PP_SEQ_FOR_EACH_I(TASKS_PROVIDER_ARG_NAME, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

/// since fruit does not provide multi-binding dependency injection, tasks vector has to be registered explicitly.
#define MAKE_TASKS_PROVIDER(...)                                                             \
[](TASKS_PROVIDER_PARAMS(__VA_ARGS__)) {                                                     \
auto v = std::vector<shared_ptr<core::Task>> {TASKS_PROVIDER_ARGS(__VA_ARGS__)};             \
return v;                                                                                    \
}

#define shared_factory(x) std::function<shared_ptr<x>()>
#define unique_factory(x) std::function<unique_ptr<x>()>
#define unique_factory_p(x, ...) std::function<unique_ptr<x>(__VA_ARGS__)>
#define MakeUniqueFactoryP(x, ...) unique_factory_p(x, __VA_ARGS__)
// if the build type is not debug then set app_debug to false

//#ifndef NDEBUG
//#endif

#endif //ENTRANCE_MONITOR_V2_INIT_H
