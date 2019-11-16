#include <gtest/gtest.h>
#include "../include/interfaces.h"

using namespace std;

TEST(interfaces, member){
	MuseumNetwork rnm("files/network_config.sadjson");

	//EXPECT_THROW(MemberInterface(rnm, 1), NoSuchCard);
	MemberInterface inter(rnm, 123);

	inter.show();
}
