//
// Created by jamal on 30/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_IO_CONTEXT_IMPL_H
#define ENTRANCE_MONITOR_V2_CORE_IO_CONTEXT_IMPL_H

#include <core/io_context.h>

namespace core::impl {
    class IoContextImpl : public IoContext {
    private:
        shared_ptr<boost::asio::io_context> ctx_;
    public:
        INJECT(IoContextImpl());

        shared_ptr<boost::asio::io_context> get_context() override;

        operator shared_ptr<boost::asio::io_context>() const override;

        size_t run() override;

    };
}

#endif //ENTRANCE_MONITOR_V2_CORE_IO_CONTEXT_IMPL_H
