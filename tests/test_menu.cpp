#include "../include/menu.h"
#include <gtest/gtest.h>

using namespace std;

void
test1()
{
  cout << "1";
  return;
};
void
test3()
{
  cout << "1";
  return;
};
void
test2()
{
  cout << "AHHHHHHHHHHHHHHHHHHHHH";
  return;
};
void
test4()
{
  cout << "4";
  return;
};

TEST(menu, normal)
{
  try {
    MenuSelect m1("This is a fun1", test1);
    MenuSelect m2("This is a fun2", test2);
    MenuSelect m3("This is a fun3", test3);
    MenuSelect m4("This is a fun4", test4);
    vector<Menu*> menu_sec_opt   = { &m1, &m2, &m3, &m4 };
    MenuOptions menu_sec         = { "Menu Secundario", menu_sec_opt };
    vector<Menu*> menu_princ_opt = { &m1, &menu_sec };
    MenuOptions menu_princ("Menu Primario", menu_princ_opt);
    menu_princ.show();
  }
  catch (...) {
    EXPECT_EQ(true, false);
  }
}

TEST(menu, filter)
{
  int d = 0;
  MenuSelectFilter<int> add1("Adiciona 1", [](int& a) { a++; });
  MenuSelectFilter<int> add2("Adiciona 2", [](int& a) { a += 2; });
  vector<MenuFilter<int>*> menu_add_opt = { &add1 };

  MenuSelectFilter<int> sub1("Subtrai 1", [](int& a) { a--; });
  MenuSelectFilter<int> sub2("Subtrai 2", [](int& a) { a -= 2; });
  vector<MenuFilter<int>*> menu_sub_opt = { &sub1, &sub2 };
  MenuOptionsFilter<int> menu_sub("Subtrair", menu_sub_opt);

  MenuSelectFilter<int> mult("Multiplica por 3", [](int& a) { a *= 3; });
  vector<MenuFilter<int>*> menu_princ_opt = { &mult, &menu_sub };
  MenuOptionsFilter<int> menu_princ("Operaçoes:", menu_princ_opt, [](int& a) {
    cout << "Result: " << a << endl;
    ;
  });

  menu_princ.show();
}

TEST(menu, mixture)
{
  try {
    MenuSelect m1("This is a fun1", test1);
    MenuSelect m2("This is a fun2", test2);
    MenuSelect m3("This is a fun3", test3);
    MenuSelect m4("This is a fun4", test4);
    vector<Menu*> menu_sec_opt = { &m1, &m2, &m3, &m4 };
    MenuOptions menu_sec       = { "Menu Secundario", menu_sec_opt };

    MenuSelectFilter<int> add1("Adiciona 1", [](int& a) { a++; });
    MenuSelectFilter<int> add2("Adiciona 2", [](int& a) { a += 2; });
    vector<MenuFilter<int>*> menu_add_opt = { &add1, &add2 };

    MenuSelectFilter<int> sub1("Subtrai 1", [](int& a) { a--; });
    MenuSelectFilter<int> sub2("Subtrai 2", [](int& a) { a -= 2; });
    vector<MenuFilter<int>*> menu_sub_opt = { &sub1, &sub2 };
    MenuOptionsFilter<int> menu_sub("Subtrair", menu_sub_opt);

    MenuSelectFilter<int> mult("Multiplica por 3", [](int& a) { a *= 3; });
    vector<MenuFilter<int>*> menu_sec2_opt = { &menu_sub, &mult };

    MenuOptionsFilter<int> menu_sec2("Operaçoes:", menu_sec2_opt, [](int& a) {
      cout << "Result: " << a << endl;
    });

    vector<Menu*> menu_princ_opt = { &m1, &menu_sec, &menu_sec2 };
    MenuOptions menu_princ("Menu Primario", menu_princ_opt);
    menu_princ.show();
  }
  catch (...) {
    EXPECT_EQ(true, false);
  }
}
