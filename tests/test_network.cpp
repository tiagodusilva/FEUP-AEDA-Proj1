#include "../include/museum_network.h"
#include <gtest/gtest.h>

#include <sstream>

using namespace std;

TEST(network, DISABLED_add_and_list_cards)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";
  IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
  UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
  SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
    s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
    s3("Leonel",
       "DAqules que e fixe",
       12345,
       Date(2015, 12, 1),
       Address("Barcelos"));
  rnm.addCard(&i1);
  rnm.addCard(&u1);
  rnm.addCard(&s1);
  rnm.addCard(&s3);

  SilverCard s5("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga"));
  // ASSERT_THROW(rnm.addCard(&s5), CardAlreadyExists);
  ASSERT_EQ(rnm.getCards().size(), 4);

  vector<Card*> vec = { &i1, &u1 };
  rnm.listCards(vec);
  // rnm.listCards(rnm.getCards());
}

TEST(network, DISABLED_remcards)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";
  IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
  UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
  SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
    s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
    s3("Leonel",
       "DAqules que e fixe",
       12345,
       Date(2015, 12, 1),
       Address("Barcelos"));
  rnm.addCard(&i1);
  rnm.addCard(&u1);
  rnm.addCard(&s1);
  rnm.addCard(&s3);

  ASSERT_EQ(rnm.getCards().size(), 4);

  IndividualCard d1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
  UniCard d2("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
  std::vector<Card*> vec{ &d1, &d2 };

  rnm.removeCards(vec);
  ASSERT_EQ(rnm.getCards().size(), 2);
  // ASSERT_THROW(rnm.removeCard(&d1), NoSuchCard);
  // rnm.listCards(rnm.getCards());
}

TEST(network, DISABLED_enterprises)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";
  set<Event> e;

  Enterprise e1("Moreira", "912", Address("Porto")),
    e2("Noice", "123", Address("Porto")), e3("Lul", "132", Address("noice"));

  vector<Enterprise> vec = { e3 };

  rnm.addEnterprise(e1);
  rnm.addEnterprise(e2);

  EXPECT_EQ(rnm.getEnterprises().size(), 2);
  // EXPECT_THROW(rnm.addEnterprise(e1), EnterpriseAlreadyExists);
  // EXPECT_THROW(rnm.listEnterprises(vec), NoSuchEnterprise); This throws
  // nothing becaus when coming from menu all of the enterprises provided are
  // valid

  rnm.listEnterprises();
}

TEST(network, modify_museums)
{
  MuseumNetwork rnm;
  Museum m1("M1",
            Time(9, 30),
            Time(19, 00),
            2,
            Address("Evora"),
            tuple<float, float>(165.23, 1231.4)),
    m2("M2",
       Time(10, 30),
       Time(20, 00),
       2,
       Address("Porto"),
       tuple<float, float>(0, 0)),
    m3("M3",
       Time(11, 20),
       Time(21, 30),
       2,
       Address("Lisboa"),
       tuple<float, float>(15.23, 11.4));

  rnm.addMuseum(m1);
  rnm.addMuseum(m2);
  rnm.addMuseum(m3);

  Event e1(
    "1", 23, 5, "Loc. Porto", Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
    e2("2", 23, 2, "Loc. Asd", Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
    e3("3", 10, 3, "Loc. Opa", Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
    e4(
      "4", 10, 6, "Loc. Nice", Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
    e5("5",
       15,
       8,
       "Loc. Evora",
       Address("Evora"),
       Time(9, 50),
       Date(2030, 7, 15)),
    e6("6",
       30,
       9,
       "Loc. Aveirso",
       Address("Aveirso"),
       Time(11, 10),
       Date(2001, 10, 5)),
    e7("7",
       30,
       8,
       "Loc. Faro",
       Address("Faro"),
       Time(20, 30),
       Date(2001, 11, 3));

  set<Event> set1 = { e1, e2, e3 };
  set<Event> set2 = { e4, e5, e6 };
  set<Event> set3 = { e7 };

  Enterprise ent1("Moreira", "912", Address("Porto"), set1),
    ent2("Noice", "123", Address("Porto"), set2),
    ent3("Lul", "132", Address("noice"), set3);

  rnm.addEnterprise(ent1);
  rnm.addEnterprise(ent2);
  rnm.addEnterprise(ent3);

  rnm.modifyMuseum(m2, m1);
  rnm.modifyMuseum(m3, m1);
//  EXPECT_EQ(rnm.getMuseums().at(0).get_name(), m1.get_name());
//  EXPECT_EQ(rnm.getMuseums().at(1).get_name(), m1.get_name());
//  EXPECT_EQ(rnm.getMuseums().at(2).get_name(), m1.get_name());

  rnm.modifyEnterprise(ent2, ent1);
  rnm.modifyEnterprise(ent3, ent1);
  EXPECT_EQ(rnm.getEnterprises().at(0).get_name(), ent1.get_name());
  EXPECT_EQ(rnm.getEnterprises().at(1).get_name(), ent1.get_name());
  EXPECT_EQ(rnm.getEnterprises().at(2).get_name(), ent1.get_name());

  /*rnm.listEnterprises();
  rnm.listMuseums();*/
}

TEST(network, DISABLED_museums)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";

  Museum m1("M1",
            Time(9, 30),
            Time(19, 00),
            2,
            Address("Evora"),
            tuple<float, float>(165.23, 1231.4)),
    m2("M2",
       Time(10, 30),
       Time(20, 00),
       2,
       Address("Porto"),
       tuple<float, float>(165.23, 1231.4)),
    m3("M3",
       Time(11, 20),
       Time(21, 30),
       2,
       Address("Lisboa"),
       tuple<float, float>(165.23, 1231.4));

  vector<Museum> vec = { m3 };

  rnm.addMuseum(m1);
  rnm.addMuseum(m2);

  EXPECT_EQ(rnm.getMuseums().size(), 2);
  // EXPECT_THROW(rnm.addMuseum(m1), MuseumAlreadyExists);
  // EXPECT_THROW(rnm.listEnterprises(vec), NoSuchEnterprise); This throws
  // nothing becaus when coming from menu all of the enterprises provided are
  // valid

  // rnm.listMuseums();
  // rnm.listMuseums(vec);
}

TEST(network, DISABLED_getEvents)
{
  MuseumNetwork rnm;

  Event e1(
    "1", 23, 5, "Loc. Porto", Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
    e2("2", 23, 2, "Loc. Asd", Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
    e3("3", 10, 3, "Loc. Opa", Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
    e4(
      "4", 10, 6, "Loc. Nice", Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
    e5("5",
       15,
       8,
       "Loc. Evora",
       Address("Evora"),
       Time(9, 50),
       Date(2030, 7, 15)),
    e6("6",
       30,
       9,
       "Loc. Aveirso",
       Address("Aveirso"),
       Time(11, 10),
       Date(2001, 10, 5)),
    e7("7",
       30,
       8,
       "Loc. Faro",
       Address("Faro"),
       Time(20, 30),
       Date(2001, 11, 3));

  set<Event> set1 = { e1, e2, e3 };
  set<Event> set2 = { e4, e5, e6 };
  set<Event> set3 = { e7 };

  Enterprise ent1("Moreira", "912", Address("Porto"), set1),
    ent2("Noice", "123", Address("Porto"), set2),
    ent3("Lul", "132", Address("noice"), set3);

  rnm.addEnterprise(ent1);
  rnm.addEnterprise(ent2);
  rnm.addEnterprise(ent3);

  ASSERT_EQ(rnm.getEvents().size(), 7);
  // rnm.listEvents();
}

TEST(network, DISABLED_export_museums)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";
  set<Event> e;

  Museum m1("M1",
            Time(9, 30),
            Time(19, 00),
            2,
            Address("Evora"),
            tuple<float, float>(165.23, 1231.4)),
    m2("M2",
       Time(10, 30),
       Time(20, 00),
       2,
       Address("Porto"),
       tuple<float, float>(165.23, 1231.4)),
    m3("M3",
       Time(11, 20),
       Time(21, 30),
       2,
       Address("Lisboa"),
       tuple<float, float>(165.23, 1231.4));

  vector<Museum> vec = { m3 };

  rnm.addMuseum(m1);
  rnm.addMuseum(m2);
  rnm.exportMuseums("files/museums.txt");
}

TEST(network, DISABLED_export_cards)
{
  MuseumNetwork rnm;
  string delim = "\n_---------------------_\n";
  IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
  UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
  SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
    s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
    s3("Leonel",
       "DAqules que e fixe",
       12345,
       Date(2015, 12, 1),
       Address("Barcelos"));
  rnm.addCard(&i1);
  rnm.addCard(&u1);
  rnm.addCard(&s1);
  rnm.addCard(&s3);

  rnm.exportCards("files/cards.txt");
}

TEST(network, DISABLED_export_enterprises)
{
  MuseumNetwork rnm;

  Event e1(
    "1", 23, 5, "Loc. Porto", Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
    e2("2", 23, 2, "Loc. Asd", Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
    e3("3", 10, 3, "Loc. Opa", Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
    e4(
      "4", 10, 6, "Loc. Nice", Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
    e5("5",
       15,
       8,
       "Loc. Evora",
       Address("Evora"),
       Time(9, 50),
       Date(2030, 7, 15)),
    e6("6",
       30,
       9,
       "Loc. Aveirso",
       Address("Aveirso"),
       Time(11, 10),
       Date(2001, 10, 5)),
    e7("7",
       30,
       8,
       "Loc. Faro",
       Address("Faro"),
       Time(20, 30),
       Date(2001, 11, 3));

  set<Event> set1 = { e1, e2, e3 };
  set<Event> set2 = { e4, e5, e6 };
  set<Event> set3 = { e7 };

  Enterprise ent1("Moreira", "912", Address("Porto"), set1),
    ent2("Noice", "123", Address("Porto"), set2),
    ent3("Lul", "132", Address("noice"), set3);

  rnm.addEnterprise(ent1);
  rnm.addEnterprise(ent2);
  rnm.addEnterprise(ent3);

  rnm.exportEnterprises("files/enterprises.txt");
}

TEST(network, DISABLED_export_network)
{
  MuseumNetwork rnm;

  Event e1(
    "1", 23, 5, "Loc. Porto", Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
    e2("2", 23, 2, "Loc. Asd", Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
    e3("3", 10, 3, "Loc. Opa", Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
    e4(
      "4", 10, 6, "Loc. Nice", Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
    e5("5",
       15,
       8,
       "Loc. Evora",
       Address("Evora"),
       Time(9, 50),
       Date(2030, 7, 15)),
    e6("6",
       30,
       9,
       "Loc. Aveirso",
       Address("Aveirso"),
       Time(11, 10),
       Date(2001, 10, 5)),
    e7("7",
       30,
       8,
       "Loc. Faro",
       Address("Faro"),
       Time(20, 30),
       Date(2001, 11, 3));

  set<Event> set1 = { e1, e2, e3 };
  set<Event> set2 = { e4, e5, e6 };
  set<Event> set3 = { e7 };

  Enterprise ent1("Moreira", "912", Address("Porto"), set1),
    ent2("Noice", "123", Address("Porto"), set2),
    ent3("Lul", "132", Address("noice"), set3);

  rnm.addEnterprise(ent1);
  rnm.addEnterprise(ent2);
  rnm.addEnterprise(ent3);

  IndividualCard i1("Rosetta", "Stoned", 123, Date(), Address("Porto"));
  UniCard u1("Fernando", "Namora", 134, Date(2000, 5, 27), Address("Lisboa"));
  SilverCard s1("Pimenta", "Machado", 234567, Date(), Address("Evora")),
    s2("Opa", "Nsei", 123, Date(1000, 11, 1), Address("Braga")),
    s3("Leonel",
       "DAqules que e fixe",
       12345,
       Date(2015, 12, 1),
       Address("Barcelos"));
  rnm.addCard(&i1);
  rnm.addCard(&u1);
  rnm.addCard(&s1);
  rnm.addCard(&s3);

  Museum m1("M1",
            Time(9, 30),
            Time(19, 00),
            2,
            Address("Evora"),
            tuple<float, float>(165.23, 1231.4)),
    m2("M2",
       Time(10, 30),
       Time(20, 00),
       2,
       Address("Porto"),
       tuple<float, float>(165.23, 1231.4)),
    m3("M3",
       Time(11, 20),
       Time(21, 30),
       2,
       Address("Lisboa"),
       tuple<float, float>(165.23, 1231.4));

  vector<Museum> vec = { m3 };

  rnm.addMuseum(m1);
  rnm.addMuseum(m2);

  rnm.exportFiles(
    "files/cards.txt", "files/museums.txt", "files/enterprises.txt", "files/repair_enterprises.txt", "files/workers.txt");
}

TEST(network, DISABLED_remove_events)
{
  MuseumNetwork rnm;

  // rnm.importFiles("111");
  // int len = rnm.getEvents().size();
  int len = 0;

  Event e1(
    "1", 23, 5, "Loc. Porto", Address("Porto"), Time(9, 0), Date(2002, 9, 11)),
    e2("2", 23, 2, "Loc. Asd", Address("Asd"), Time(11, 0), Date(2011, 9, 21)),
    e3("3", 10, 3, "Loc. Opa", Address("Opa"), Time(15, 0), Date(2019, 4, 4)),
    e4(
      "4", 10, 6, "Loc. Nice", Address("Nice"), Time(20, 0), Date(2020, 1, 11)),
    e5("5",
       15,
       8,
       "Loc. Evora",
       Address("Evora"),
       Time(9, 50),
       Date(2030, 7, 15)),
    e6("6",
       30,
       9,
       "Loc. Aveirso",
       Address("Aveirso"),
       Time(11, 10),
       Date(2001, 10, 5)),
    e7("7",
       30,
       8,
       "Loc. Faro",
       Address("Faro"),
       Time(20, 30),
       Date(2001, 11, 3));

  set<Event> set1 = { e1, e2, e3 };
  set<Event> set2 = { e4, e5, e6 };

  Enterprise ent1("Ent1", "912", Address("Opa"), set1),
    ent2("Ent2", "123", Address("Nice"), set2);

  rnm.addEnterprise(ent1);
  rnm.addEnterprise(ent2);

  ASSERT_GE(rnm.getEnterprises().size(),
            2); // This test only works if there are more than two enterprises

  //	rnm.addEvent(ent1, e1); rnm.addEvent(ent1, e2); rnm.addEvent(ent1, e3);
  // rnm.addEvent(ent1, e4); 	rnm.addEvent(ent2, e5); rnm.addEvent(ent2, e6);
  // rnm.addEvent(ent2, e7);

  vector<Event> vec = { e1, e2, e3, e4, e5, e6 };
  ASSERT_EQ(rnm.getEvents().size(), len + 6);

  rnm.removeEvents(vec);

  ASSERT_EQ(rnm.getEvents().size(), len);
}

TEST(network, DISABLED_import_cards)
{
  MuseumNetwork rnm;

  rnm.importCards("files/cards.txt");
  ASSERT_EQ(rnm.getCards().size(), 4);
  // rnm.listCards();
}

TEST(network, DISABLED_import_museums)
{
  MuseumNetwork rnm;

  rnm.importMuseums("files/museums.txt");
  ASSERT_EQ(rnm.getMuseums().size(), 2);
  // rnm.listMuseums();
}

TEST(network, DISABLED_import_enterprises)
{
  MuseumNetwork rnm;

  rnm.importEnterprises("files/enterprises.txt");
  ASSERT_EQ(rnm.getEnterprises().size(), 3);
  // rnm.listEnterprises();
}

TEST(network, DISABLED_import_network)
{
  MuseumNetwork rnm;

  rnm.importFiles("files/network_config.sadjson");
  // rnm.listEnterprises();
  rnm.listMuseums();
  rnm.listCards();
  rnm.listEvents();
}
