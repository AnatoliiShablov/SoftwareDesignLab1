#ifndef LRUCACHE_HPP
#define LRUCACHE_HPP

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <list>
#include <optional>
#include <unordered_map>

template <typename T>
void moveToFront(std::list<T>& list, typename std::list<T>::iterator it) {
    if (it != list.begin()) {
        list.splice(list.begin(), list, it, std::next(it));
    }
}

template <class Key, class T, class Hash = std::hash<Key>, class KeyEqual = std::equal_to<Key>>
class LRUCache {
public:
    using key_type        = Key;
    using mapped_type     = T;
    using reference       = std::optional<key_type&>;
    using const_reference = std::optional<key_type const&>;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;
    using hasher          = Hash;
    using key_equal       = KeyEqual;

    constexpr static size_type DefaultCacheCapacity = 10;

    LRUCache(size_type capacity = DefaultCacheCapacity) noexcept : _capacity{capacity == 0 ? 1 : capacity} {
        assert(_capacity > 0);
    }

    [[nodiscard]] const_reference get(key_type const& key) const noexcept {
        return _moveKeyToFront(key) ? _orderedReferences.front().second : std::nullopt;
    }

    [[nodiscard]] reference get(key_type const& key) noexcept {
        return _moveKeyToFront(key) ? _orderedReferences.front().second : std::nullopt;
    }

    void put(key_type key, mapped_type value) {
        if (!_idMap.contains(key) && _orderedReferences.size() == _capacity) {
            auto const& lastKey = _orderedReferences.back().first;
            _idMap.erase(lastKey);
            _orderedReferences.pop_back();
        }

        if (_moveKeyToFront(key)) {
            _idMap[key] = std::move(value);
        } else {
            auto [iterator, _] = _idMap.emplace(std::move(key), _orderedReferences.end());
            _orderedReferences.emplace_front(iterator->first, std::move(value));
            iterator->second = _orderedReferences.begin();
        }
    }

    [[nodiscard]] size_type size() const noexcept { return _idMap.size(); }

    [[nodiscard]] bool empty() const noexcept { return size() == 0; }

private:
    bool _moveKeyToFront(key_type const& key) const {
        bool contains = _idMap.contains(key);
        if (contains) {
            moveToFront(_orderedReferences, _idMap.at(key));
        }
        return contains;
    }

    const size_type _capacity;

    mutable std::list<std::pair<key_type const&, mapped_type>> _orderedReferences;
    std::unordered_map<key_type, typename decltype(_orderedReferences)::iterator, hasher, key_equal> _idMap;
};

#endif
