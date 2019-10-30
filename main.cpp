#include <gtest/gtest.h>
#include <gtest/gtest.h>

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    // Specify test name by setting filter to TESTNAME*
    testing::GTEST_FLAG(filter) = "menu*";
    return RUN_ALL_TESTS();
}