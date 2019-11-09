#include <gtest/gtest.h>
#include "../include/menu.h"

using namespace std;

void test1() { cout << "1"; return;};
void test3() { cout << "1"; return;};
void test2() { cout << "AHHHHHHHHHHHHHHHHHHHHH"; return;};
void test4() { cout << "4"; return;};

TEST(menu, DISABLED_normal){
    try {
        MenuSelelect m1("This is a fun1", test1);
       MenuSelelect m2("This is a fun2", test2);
       MenuSelelect m3("This is a fun3", test3);
       MenuSelelect m4("This is a fun4", test4);
       vector<Menu*> menu_sec_opt = {&m1, &m2, &m3, &m4};
       MenuOptions menu_sec = {"Menu Secundario", menu_sec_opt};
        vector<Menu*> menu_princ_opt = {&m1, &menu_sec};
        MenuOptions menu_princ("Menu Primario", menu_princ_opt);
        menu_princ.show();
    }
    catch(...) {
        EXPECT_EQ(true, false);
    }
}


TEST(menu, DISABLED_filter){
	int d=0;
	MenuSelelectFilter<int> add1("Adiciona 1", [](int &a){ a++; });
	MenuSelelectFilter<int> add2("Adiciona 2", [](int &a){ a+=2; });
	vector<MenuFilter<int>*> menu_add_opt = {&add1, &add2};
	MenuOptionsFilter<int> menu_add("Adicionar", menu_add_opt, [](int){}, true);

	MenuSelelectFilter<int> sub1("Subtrai 1", [](int &a){ a--; });
	MenuSelelectFilter<int> sub2("Subtrai 2", [](int &a){ a-=2; });
	vector<MenuFilter<int> *> menu_sub_opt = {&sub1, &sub2};
	MenuOptionsFilter<int> menu_sub("Subtrair", menu_sub_opt);

	MenuSelelectFilter<int> mult("Multiplica por 3", [](int &a){ a*=3; });
	vector<MenuFilter<int>*> menu_princ_opt = {&menu_add, &menu_sub, &mult};
	MenuOptionsFilter<int> menu_princ("Operaçoes:", menu_princ_opt, [](int &a){ cout << "Result: " << a << endl;; });

	menu_princ.show();
}


TEST(menu, mixture){
    try {
		MenuSelelect m1("This is a fun1", test1);
		MenuSelelect m2("This is a fun2", test2);
		MenuSelelect m3("This is a fun3", test3);
		MenuSelelect m4("This is a fun4", test4);
		vector<Menu*> menu_sec_opt = {&m1, &m2, &m3, &m4};
		MenuOptions menu_sec = {"Menu Secundario", menu_sec_opt};

		MenuSelelectFilter<int> add1("Adiciona 1", [](int &a){ a++; });
		MenuSelelectFilter<int> add2("Adiciona 2", [](int &a){ a+=2; });
		vector<MenuFilter<int>*> menu_add_opt = {&add1, &add2};
		MenuOptionsFilter<int> menu_add("Adicionar", menu_add_opt, [](int){}, true);

		MenuSelelectFilter<int> sub1("Subtrai 1", [](int &a){ a--; });
		MenuSelelectFilter<int> sub2("Subtrai 2", [](int &a){ a-=2; });
		vector<MenuFilter<int> *> menu_sub_opt = {&sub1, &sub2};
		MenuOptionsFilter<int> menu_sub("Subtrair", menu_sub_opt);

		MenuSelelectFilter<int> mult("Multiplica por 3", [](int &a){ a*=3; });
		vector<MenuFilter<int>*> menu_sec2_opt = {&menu_add, &menu_sub, &mult};

		MenuOptionsFilter<int> menu_sec2("Operaçoes:", menu_sec2_opt, [](int &a){ cout << "Result: " << a << endl; });

		vector<Menu*> menu_princ_opt = {&m1, &menu_sec, &menu_sec2};
		MenuOptions menu_princ("Menu Primario", menu_princ_opt);
		menu_princ.show();
    }
    catch(...) {
        EXPECT_EQ(true, false);
	}
}
