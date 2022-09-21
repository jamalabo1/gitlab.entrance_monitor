//
// Created by jamal on 13/08/2022.
//

#include <core/amqp/connection_factory.h>
#include <results_aggregator/results_aggregator.h>

#include <core/logging.h>
#include <core/consumer_factory.h>
#include <core/gui_handler.h>

#include <view_models/computed_result_view.h>


#include "blocking_result_message_handler.h"

#include <utils/service.h>

#include <boost/asio.hpp>


using namespace std;
using namespace fruit;
using namespace core;


ResultsAggregatorService::ResultsAggregatorService(core::consume::Consumer *consumer,
                                                   core::consume::ConsumerMessageHandler *handler,
                                                   core::communication::publish::PublisherFactory *publisher_factory,
                                                   core::IoRunner *io_runner,
                                                   Aggregator *aggregator) : TaskService(io_runner),
                                                                             consumer(consumer),
                                                                             handler(handler),
                                                                             aggregator(aggregator) {
    publisher = publisher_factory->create_publisher("results.{1}");
};

void ResultsAggregatorService::graph_computation() {
    double result = aggregator->aggregate();
    ComputedResultView view(result > 0.5);

    publisher->publish(view);
}

int ResultsAggregatorService::setup() {


    BOOST_LOG_TRIVIAL(debug) << "Running result aggregator service";

    boost::asio::io_context io;

    auto timer_schedule = boost::asio::chrono::seconds(5);

    boost::asio::steady_timer t(io, timer_schedule);

    BOOST_LOG_TRIVIAL(debug) << "Binding async function callback";
    function<void(const boost::system::error_code &)> fn;

    // TODO: replace this with the coming feature of `io_runner` `IoRunner::schedule`
    fn = [this, &t, &fn, &timer_schedule](const boost::system::error_code &ec) {
        this->graph_computation();
        t.expires_from_now(timer_schedule);
        t.async_wait(fn);
    };
    t.async_wait(fn);


    BOOST_LOG_TRIVIAL(debug) << "Creating consumer service runner";


    post([&io]() { io.run(); });


    CREATE_CONSUMER_SERVICE_RUNNER("blocking.{1}");

    return run();
}


ResultAggregatorServiceComponent getResultsAggregatorServiceComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getBlockingResultMessageHandlerComponent)
            .install(getAggregatorComponent)
            .addMultibinding<TaskService, ResultsAggregatorService>();
}
