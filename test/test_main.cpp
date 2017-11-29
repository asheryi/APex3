
#include <gtest/gtest.h>

using namespace testing;

GTEST_API_ int main(int argc, char *argv[]) {
    InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}