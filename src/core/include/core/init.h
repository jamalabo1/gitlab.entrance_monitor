//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_INIT_H
#define ENTRANCE_MONITOR_V2_INIT_H

// TODO: flip the include dependency from sub-headers including the core headers to the opposite
#include <utils/macros.h>
#include <fruit/fruit.h>
#include <core/ptrs.h>
#include <core/configurations.h>

#include <boost/mp11.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
//using namespace boost::mp11;
//
//namespace {
//    template<class... T>
//    struct typelist {
//    };
////typedef boost::mp11::mp_list<T...> typelist<T...>;
////    template<class... T>
////using typelist<T...> = boost::mp11::mp_list<T...>;
//
//    class IExported {
//    };
//}
//
//template<typename ... T>
//fruit::Component<T...> foo(typelist<T...>);
//
//template<typename ...L>
//using componentFromTypelist = decltype(foo( std::declval<L>()... ));
//
//template<template<class...> class... TL, typename... T>
//typelist<T...> combine_typelist(typelist<T...>...);
//
//
////using l1 = mp_list<int, double>;
////using l2 = mp_list<int, long>;
////
////using r = mp_append<l1, l2>;
//
////using comp = mp_unique<mp_rename<r, fruit::Component>>;
////
////comp funct() {
////
////}
//
//using combined_typelist = decltype(combine_typelist(  std::declval<  typelist<int, double>   >()   )  );
////template<typename ...L>
////using expander =
////using test2 = componentFromTypelist<  typelist<int, float> >;
////using test = decltype(foo(  std::declval<   typelist<int, double>  >()     ));

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

//#define $typelist

template<typename... T>
class $typelist {
public:

//    template<typename TL>
//    constexpr typelist<> get_type() {
//        if(std::is_same<TL, IExported>()) return TL;
//        return typelist<TL>;
//    }
    using Typenames = typelist<T...>;

//    using Typenames = mergeTypelist(boost::mp11::mp_if<std::is_convertible<IExported, T>, typename T::Typenames, typelist<T>>...);
};

// exported class is a container/wrapper/holder for pack expansion to export types.
template<typename...Ts>
class $Exported : public IExported {
public:


    // if t is $Exported then take types from it.
    // if not then add it to the typelist

//    using Typenames = mergeTypelist(    boost::mp11::mp_if< >    );
    using Typenames = typelist<Ts...>;


    template<class... TR>
    using Component = MakeComponentFromTypeListWithRequired(MakeRequiredComponentsFromTypeList(typename $typelist<TR...>::Typenames), Typenames);

    using PureComponent = Component<>;
};

template<typename... $TE>
class $Module : public IExported {
public:
//    using Typenames = boost::mp11::mp_flatten<mergeTypelist(typename $TE::Typenames...)>;
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
