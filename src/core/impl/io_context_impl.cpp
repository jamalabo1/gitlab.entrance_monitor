//
// Created by jamal on 30/08/2022.
//
#include "io_context_impl.h"

using fruit::createComponent;

core::impl::IoContextImpl::IoContextImpl() {
    ctx_ = make_shared<boost::asio::io_context>();
}


shared_ptr<boost::asio::io_context> core::impl::IoContextImpl::get_context() {
    return ctx_;
}

core::impl::IoContextImpl::operator shared_ptr<boost::asio::io_context>() const {
    return ctx_;
}

size_t core::impl::IoContextImpl::run() {
    return ctx_->run();
}

core::IoContextComponent core::getIoContextComponent() {
    return createComponent()
            .bind<IoContext, impl::IoContextImpl>();
}