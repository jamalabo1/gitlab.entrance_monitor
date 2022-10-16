//
// Created by jamal on 30/08/2022.
//
#include "io_context_impl.h"


namespace core {
    using fruit::createComponent;

    namespace impl {

        IoContextImpl::IoContextImpl() {
            ctx_ = make_shared<boost::asio::io_context>(BOOST_ASIO_CONCURRENCY_HINT_SAFE);
        }


        shared_ptr<boost::asio::io_context> IoContextImpl::get_context() {
            return ctx_;
        }

        IoContextImpl::operator shared_ptr<boost::asio::io_context>() const {
            return ctx_;
        }

        size_t IoContextImpl::run() {
            return ctx_->run();
        }
    }


    IoContextComponent getIoContextComponent() {
        return createComponent()
                .bind<IoContext, impl::IoContextImpl>();
    }
}
