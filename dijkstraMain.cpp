#include <gtest/gtest.h>
#include "Dijkstra.h"

TEST(Dijkstra, VerifyImplementation) {
    std::vector<std::vector<int>> m1 {
        {0, 3, 5, 10},
        {3, 0, 0, 2},
        {5, 0, 0, 3},
        {10, 2, 3, 0}
    };

    std::vector<std::vector<int>> m2 {
        {0, 4, 0, 0, 0, 0, 0, 8, 0},
        {4, 0, 8, 0, 0, 0, 0, 11, 0},
        {0, 8, 0, 7, 0, 0, 0, 0, 2},
        {0, 0, 7, 0, 9, 14, 0, 0, 0},
        {0, 0, 0, 9, 0, 10, 0, 0, 0},
        {0, 0, 0, 14, 10, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 2, 0, 1, 6},
        {8, 11, 0, 0, 0, 0, 1, 0, 7},
        {0, 0, 2, 0, 0, 0, 6, 7, 0}
    };

    Dijkstra obj1(m1);
    Dijkstra obj2(m2);

    std::vector<int> res1{0, 3, 5, 5};
    std::vector<int> res12{3, 0, 5, 2};
    std::vector<int> res2{0, 4, 12, 19, 21, 11, 9, 8, 14};

    EXPECT_EQ(res1, obj1.findShortestPath(0));
    EXPECT_EQ(res12, obj1.findShortestPath(1));
    EXPECT_EQ(res2, obj2.findShortestPath(0));
}

TEST(Dijkstra, InvalidNodeInput) {
    std::vector<std::vector<int>> m1 {
        {0, 3, 5, 10},
        {3, 0, 0, 2},
        {5, 0, 0, 3},
        {10, 2, 3, 0}
    };

    Dijkstra obj1(m1);
    EXPECT_THROW({ obj1.findShortestPath(7); }, std::out_of_range);
    EXPECT_THROW({ obj1.findShortestPath(12); }, std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
