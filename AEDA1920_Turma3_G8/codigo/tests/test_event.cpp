#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/event.h"

using namespace std;

TEST(events, files) {
    Event ev1("Event", 15.75, 20, "Location Name",Address("Region"), Time(16, 0), Date(2019, 12, 25));

    ofstream tofile("events.txt");
    tofile << ev1;
    tofile.close();

    Event ev2;

    ifstream fromfile("events.txt");
    fromfile >> ev2;
    fromfile.close();

    //cout << ev1 << endl;
    //cout << "EV2" << endl;
    //cout << ev2 << endl;

    ASSERT_EQ(ev1.get_id() + 1, ev2.get_id());
    ASSERT_EQ(ev1.get_name(), ev2.get_name());
    ASSERT_EQ(ev1.get_location_name(), ev2.get_location_name());
    ASSERT_EQ(ev1.get_address(), ev2.get_address());
    ASSERT_EQ(ev1.get_fee(), ev2.get_fee());
    ASSERT_EQ(ev1.get_current_capacity(), ev2.get_current_capacity());
    ASSERT_EQ(ev1.get_max_capacity(), ev2.get_max_capacity());
    ASSERT_EQ(ev1.get_time(), ev2.get_time());
    ASSERT_EQ(ev1.get_date(), ev2.get_date());
}
