//
// Created by jamal on 23/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PTRS_H
#define ENTRANCE_MONITOR_V2_PTRS_H

#include <boost/shared_ptr.hpp>
#include <memory>

using std::shared_ptr;
using std::make_shared;

using std::unique_ptr;
using std::make_unique;


namespace core {
    namespace {
        template<class SharedPointer>
        struct Holder {
            SharedPointer p;

            Holder(const SharedPointer &p) : p(p) {}

            Holder(const Holder &other) : p(other.p) {}

            Holder(Holder &&other) : p(std::move(other.p)) {}

            void operator()(...) { p.reset(); }
        };
    }

    template<class T>
    std::shared_ptr<T> to_std(const boost::shared_ptr<T> &p) {
        typedef Holder<std::shared_ptr<T>> H;
        if (H *h = boost::get_deleter<H>(p)) {
            return h->p;
        } else {
            return std::shared_ptr<T>(p.get(), Holder<boost::shared_ptr<T>>(p));
        }
    }

    template<class T>
    std::shared_ptr<T> to_raw_ptr(const boost::shared_ptr<T> &p) {
        typedef Holder<std::shared_ptr<T>> H;
        if (H *h = boost::get_deleter<H>(p)) {
            return h->p;
        } else {
            return std::shared_ptr<T>(p.get(), Holder<boost::shared_ptr<T>>(p));
        }
    }


    template<class T>
    boost::shared_ptr<T> to_boost(const std::shared_ptr<T> &p) {
        typedef Holder<boost::shared_ptr<T>> H;
        if (H *h = std::get_deleter<H>(p)) {
            return h->p;
        } else {
            return boost::shared_ptr<T>(p.get(), Holder<std::shared_ptr<T>>(p));
        }
    }
}


#endif //ENTRANCE_MONITOR_V2_PTRS_H
