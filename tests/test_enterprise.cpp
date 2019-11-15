#include <fstream>
#include <gtest/gtest.h>
#include <iostream>

#include "../include/enterprise.h"

using namespace std;

TEST(enterprise, files) {
    Event ev("Event", 15.75, 20, "Location Name",Address("Street", "7654-321", "EventRegion"), Time(16, 00), Date(2019, 12, 25));
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

TEST(enterprise, add_event) {
    Enterprise ent("enterprise", "@email", Address("Rua", "1234-567", "Porto"));
    Event ev("eventus", 12.75, 20, "Conservatorio de Gaia",Address("Gaia"), Time(12, 40), Date(2019, 11, 16));

    unsigned temp_id = ev.get_id();
    ent.add_event(ev);

    ASSERT_EQ(ev.get_id(), 0);
    ASSERT_EQ(ent.get_name(), "enterprise");
    ASSERT_EQ(ent.get_contact(), "@email");
    ASSERT_EQ(ent.get_events().begin()->get_id(), temp_id);
    ASSERT_EQ(ent.get_address(), Address("Rua", "1234-567", "Porto"));
}
