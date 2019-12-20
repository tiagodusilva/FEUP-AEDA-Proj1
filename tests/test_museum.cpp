#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/museum.h"

using namespace std;

TEST(museum, files) {
    Museum m1("nome", Time(7, 0), Time(20, 0), 12.5, Address("Rua", "1234-567", "Região"), tuple<float,float>(165.23, 1231.4));

    ofstream tofile("museum.txt");
    tofile << m1;
    tofile.close();

    Museum m2;
    ifstream fromfile("museum.txt");
    fromfile >> m2;
    fromfile.close();

//    cout << m1 << endl;

    ASSERT_EQ(m1.get_name(), m2.get_name());
    ASSERT_EQ(m1.get_open(), m2.get_open());
    ASSERT_EQ(m1.get_close(), m2.get_close());
    ASSERT_EQ(m1.get_fee(), m2.get_fee());
    ASSERT_EQ(m1.get_address(), m2.get_address());
}
