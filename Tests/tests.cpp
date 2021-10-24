#include "LRUCache.hpp"
#include "gtest/gtest.h"

TEST(UtilTests, moveToFrontFirstFrom1) {
    std::list<int> a{1};
    auto copy = a;

    moveToFront(a, a.begin());
    EXPECT_EQ(a, copy);
}

TEST(UtilTests, moveToFrontFirstFrom2) {
    std::list<int> a{1, 2};
    auto copy = a;

    moveToFront(a, a.begin());
    EXPECT_EQ(a, copy);
}

TEST(UtilTests, moveToFrontSecondFrom2) {
    std::list<int> a{1, 2};
    std::list<int> res{2, 1};

    moveToFront(a, std::next(a.begin()));
    EXPECT_EQ(a, res);
}

TEST(UtilTests, moveToFrontRandom) {
    std::list<int> a{1, 2, 3, 4, 5};
    std::list<int> res{3, 1, 2, 4, 5};

    moveToFront(a, std::next(a.begin(), 2));
    EXPECT_EQ(a, res);
}

TEST(TypeTests, full) {
    LRUCache<int, bool> cache;

    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::key_type, int>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::mapped_type, bool>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::value_type, std::optional<bool>>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::size_type, std::size_t>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::difference_type, std::ptrdiff_t>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::hasher, std::hash<int>>));
    EXPECT_TRUE((std::is_same_v<typename decltype(cache)::key_equal, std::equal_to<int>>));
}

TEST(SimpleTests, empty) {
    LRUCache<int, int> cache;
    EXPECT_EQ(cache.size(), 0);
    EXPECT_TRUE(cache.empty());
    for (int i = 0; i < 10; ++i) {
        EXPECT_FALSE(cache.get(i).has_value());
    }
}

TEST(SimpleTests, oneElement) {
    LRUCache<int, int> cache;
    std::pair<int, int> test{0, 1};
    cache.put(test.first, test.second);

    EXPECT_EQ(cache.size(), 1);
    EXPECT_FALSE(cache.empty());
    EXPECT_EQ(cache.get(test.first).value(), test.second);
    for (int i = 1; i < 10; ++i) {
        EXPECT_FALSE(cache.get(i).has_value());
    }
}

TEST(SimpleTests, twoElements) {
    LRUCache<int, int> cache;
    std::pair<int, int> test1{0, 1};
    std::pair<int, int> test2{2, 3};
    cache.put(test1.first, test1.second);
    cache.put(test2.first, test2.second);

    EXPECT_EQ(cache.size(), 2);
    EXPECT_FALSE(cache.empty());
    EXPECT_EQ(cache.get(test1.first).value(), test1.second);
    EXPECT_EQ(cache.get(test2.first).value(), test2.second);
    for (int i = 3; i < 10; ++i) {
        EXPECT_FALSE(cache.get(i).has_value());
    }
}

TEST(SimpleTests, twoElementsInNoCapcity) {
    LRUCache<int, int> cache(0);
    std::pair<int, int> test1{0, 1};
    std::pair<int, int> test2{2, 3};
    cache.put(test2.first, test2.second);

    EXPECT_EQ(cache.size(), 1);
    EXPECT_FALSE(cache.empty());

    cache.put(test1.first, test1.second);

    EXPECT_EQ(cache.size(), 1);
    EXPECT_FALSE(cache.empty());

    EXPECT_EQ(cache.get(test1.first).value(), test1.second);
    for (int i = 1; i < 10; ++i) {
        EXPECT_FALSE(cache.get(i).has_value());
    }
}

TEST(BigTests, constructFromIt) {
    std::array<std::pair<int, int>, 5> test = {std::pair{0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}};
    LRUCache<int, int> cache(test.begin(), test.end(), 4);

    EXPECT_EQ(cache.size(), 4);
    EXPECT_FALSE(cache.empty());

    EXPECT_FALSE(cache.get(0).has_value());
    for (int i = 1; i < 5; ++i) {
        EXPECT_EQ(cache.get(i * 2).value(), test[i].second);
    }
}

TEST(BigTests, randomTest) {
    std::vector<int64_t> val;

    LRUCache<int64_t, bool> cache;

    for (size_t i = 0; i < 1000; ++i) {
        val.push_back((i > 1 ? val[i - 2] : 1) + (i > 0 ? val[i - 1] : 0));
        cache.put(val.back(), val.back() % 2 == 0);
        EXPECT_EQ(cache.get(val.front()).value(), false);
    }

    for (size_t i = val.size() - 9; i < val.size(); ++i) {
        EXPECT_EQ(cache.get(val[i]).value(), val[i] % 2 == 0);
    }

    EXPECT_THROW(cache.get(val[val.size() - 10]).value(), std::bad_optional_access);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
