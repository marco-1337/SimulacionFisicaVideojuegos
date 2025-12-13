#pragma once

#include <list>
#include <functional>
#include <type_traits>
#include <memory>

#include "Killable.hpp"

template <typename T>
class KillableList {
    static_assert(std::is_base_of_v<Killable, T>,"T debe heredar de Killable");
private:
    std::list<std::shared_ptr<T>> list;

public:

    KillableList() {}
 
    std::weak_ptr<T> addObject(std::unique_ptr<T> obj) {
        list.emplace_back(std::move(obj));
        return list.back();
    }

    std::weak_ptr<T> addObject(std::shared_ptr<T> obj) {
        list.emplace_back(obj);
        return list.back();
    }

    void foreachAlive(std::function<void(T&)> callback) {
       auto it = list.begin();

        while (it != list.end()) {
            if ((*it)->isAlive()) {
                callback(*(*it));
                ++it;
            }
            else {
                it = list.erase(it);
            }
        }
    }
};