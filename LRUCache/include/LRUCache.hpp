#ifndef LRUCACHE_HPP
#define LRUCACHE_HPP

#include <cstddef>
#include <cstdint>
#include <list>
#include <unordered_map>

template <typename T>
void moveToFront(std::list<T>& list, typename std::list<T>::iterator it) {
    if (it != list.begin()) {
        list.splice(list.begin(), list, it, std::next(it));
    }
}

class LRUCache {
public:
    constexpr static size_t DefaultCacheCapacity = 10;

    using IdType     = int64_t;
    using StoredType = int;

    LRUCache(size_t capacity = DefaultCacheCapacity) : _capacity{capacity} {}

    bool get(IdType id, StoredType& var) const {
        if (_idMap.contains(id)) {
            var = _idMap.at(id)->second;
            return true;
        }
        return false;
    }

    void put(StoredType id, StoredType var) {
        if (!_idMap.contains(id) && _storedValues.size() == _capacity) {
            _idMap.erase(_storedValues.back().first);
            _storedValues.pop_back();
        }

        if (_idMap.contains(id)) {
            moveToFront(_storedValues, _idMap.at(id));
            _storedValues.front().second = std::move(var);
        } else {
            _storedValues.emplace_front(id, std::move(var));
            _idMap.emplace(id, _storedValues.begin());
        }
    }

private:
    const size_t _capacity;

    std::list<std::pair<IdType, StoredType>> _storedValues;
    std::unordered_map<IdType, decltype(_storedValues)::iterator> _idMap;
};

#endif
