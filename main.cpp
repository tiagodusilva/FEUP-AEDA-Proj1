#include <gtest/gtest.h>
#include "include/interfaces.h"

int main(int argc, char* argv[]) {
	MuseumNetwork rnm;
	GUI gui(rnm);
	gui.show();
	return 0;

	//testing::InitGoogleTest(&argc, argv);
	//Specify test name by setting filter to TESTNAME
	//testing::GTEST_FLAG(filter) = "menu*";
	//testing::GTEST_FLAG(filter) = "card*";
	//return RUN_ALL_TESTS();
}
