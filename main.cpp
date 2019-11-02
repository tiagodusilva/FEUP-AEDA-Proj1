#include <gtest/gtest.h>

using namespace std;

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	// Specify test name by setting filter to TESTNAME*
	testing::GTEST_FLAG(filter) = "card*";
	testing::GTEST_FLAG(filter) = "menu*";
	return RUN_ALL_TESTS();
}
