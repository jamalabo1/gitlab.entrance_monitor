//
// Created by jamal on 12/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_VIEW_H
#define ENTRANCE_MONITOR_V2_VIEW_H

#include <string>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <utility>


#define pack_items(...) template<typename T> \
void pack(T &packer) { \
packer(id, __VA_ARGS__);                                     \
}                                                            \


namespace core {



    static auto uuid_generator = boost::uuids::random_generator();


    class ViewId {

    private:
        std::string id;


    public:
        ViewId() : ViewId(to_string(core::uuid_generator())) {
        }

        ViewId(std::string id) {
            this->id = std::move(id);
        }
        operator std::string ()  {
            return this->id;
        }
        ~ViewId()=default;

        // TODO: fix pack_items is override when used.
        pack_items(id);
    };

    class View {
    public:
        ViewId id;

        View() = default;
        ~View()= default;
    };
}
#endif //ENTRANCE_MONITOR_V2_VIEW_H
