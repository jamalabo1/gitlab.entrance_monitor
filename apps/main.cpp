//
// Created by jamal on 02/07/2022.
//

#include <core/logging.h>

#include <stream_obtainer/stream_obtainer.h>
#include <object_detector/object_detector.h>
#include <blocking_computation/blocking_computation.h>
#include <results_aggregator/results_aggregator.h>

#include <boost/asio.hpp>
#include <boost/preprocessor.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>

#include <opencv2/core/utils/logger.hpp>

using namespace std;
using namespace fruit;
using namespace core;

Component<Configurations> getSharedComponents() {
    return fruit::createComponent()
            .install(getConfigurationsComponent);
}

using ComponentFunc = function<Component<>()>;

Component<> getCreateComponent(const ComponentFunc *any) {
    return (*any)();
}

#define i_make_fruit_component(x)        [] () -> Component<> { \
return fruit::createComponent() \
.install(getSharedComponents)\
.install(x); \
}

#define make_fruit_component(x) components.emplace_back(i_make_fruit_component(x))
#define VARIADIC_MAP(r, macro, i, elem) make_fruit_component(elem);
#define compose_components(...) BOOST_PP_SEQ_FOR_EACH_I(VARIADIC_MAP, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

void init()
{
#ifdef APP_DEBUG
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_VERBOSE);
    auto log_level = boost::log::trivial::debug;
#elif
    auto log_level = boost::log::trivial::info;
#endif

    boost::log::core::get()->set_filter
            (
                    boost::log::trivial::severity >= log_level
            );
}

int main() {
    BOOST_LOG_TRIVIAL(info) << "initiating project runner";
    init();
    BOOST_LOG_TRIVIAL(info) << "Running as project runner";

    vector<ComponentFunc> components;

    compose_components(
            stream_obtainer::getStreamObtainerComponent,
            object_detector::getObjectDetectorComponent,
            blocking_computation::getBlockingComputationComponent,
            results_aggregator::getResultsAggregatorServiceComponent
    );

    boost::asio::thread_pool pool(components.size());

    vector<shared_ptr<Injector<>>> injectors;

    for (const ComponentFunc &component: components) {
        shared_ptr<Injector<>> injector = make_unique<Injector<>>(getCreateComponent, &component);

        const vector<Service *> &services = injector->getMultibindings<Service>();
        for (Service *service: services) {
            BOOST_LOG_TRIVIAL(debug) << "registered " << typeid(*service).name() << " as service";
            boost::asio::post(pool, [service] { service->setup(); });
        }

        injectors.emplace_back(injector);
    }


    BOOST_LOG_TRIVIAL(trace) << "joining pool threads (" << components.size() << ")";
    pool.join();
    BOOST_LOG_TRIVIAL(trace) << "all threads were joined";

    return 0;
}