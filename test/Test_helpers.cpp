#include "helpers.hpp"
#include "gtest/gtest.h"

class HelpersTest : public ::testing::Test{};

TEST(HelpersTest, TestName) {
    prototask::WrapperMessage wm;
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}