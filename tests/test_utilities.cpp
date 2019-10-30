#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "../include/utilities.h"
#include <sstream>
using namespace std;

TEST(utilities, getInt){
   istringstream is("asd\nooi3\nadsd\n2sds\n3");
   EXPECT_EQ(utl::getInt(is), 3);
}

TEST(utilities, getInt_withbounds){
    istringstream is("asd\nooi-3\nadsd\n-2sds\n6\n2asde\n3");
    EXPECT_EQ(utl::getInt(is, 0, 4), 3);
}
