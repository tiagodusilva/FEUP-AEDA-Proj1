#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/enterprise.h"

using namespace std;

TEST(enterprise, files) {
    Event ev("Event", 15.75, 20, Address("Street", "7654-321", "EventRegion"), Time(16, 00), Date(2019, 12, 25));
    set<Event> s = {ev};
    Enterprise ent1("EnterpriseName", "enterprise@notgoogle", Address("Street", "1234-567", "Region"), s);

    ofstream tofile("enterprise.txt");
    tofile << ent1;
    tofile.close();

    Enterprise ent2;
    ifstream fromfile("enterprise.txt");
    fromfile >> ent2;
    fromfile.close();

//    cout << "Event:" << endl << ev << endl;

//    cout << "Ent1" << endl << ent1 << endl;
//    cout << "Ent2" << endl << ent2 << endl;

//    cout << "Ev1" << endl << ent1.get_event(1) << endl;
//    cout << "Ev2" << endl << ent2.get_event(2) << endl;

    ASSERT_EQ(ent1.get_name(), ent2.get_name());
    ASSERT_EQ(ent1.get_contact(), ent2.get_contact());
    ASSERT_EQ(ent1.get_events().begin()->get_id() + 1, ent2.get_events().begin()->get_id());
    ASSERT_EQ(ent1.get_address(), ent2.get_address());
}
