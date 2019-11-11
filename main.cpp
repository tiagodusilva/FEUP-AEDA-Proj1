#include <gtest/gtest.h>
#include "include/interfaces.h"

using namespace std;

int main(int argc, char* argv[]) {
	GUI gui;
	gui.show();
	return 0;

	/*testing::InitGoogleTest(&argc, argv);
	//Specify test name by setting filter to TESTNAME*
	testing::GTEST_FLAG(filter) = "interfaces*";
	//testing::GTEST_FLAG(filter) = "card*";
	return RUN_ALL_TESTS();*/
}
