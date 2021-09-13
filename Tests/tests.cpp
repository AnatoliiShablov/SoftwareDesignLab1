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
