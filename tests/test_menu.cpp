#include <gtest/gtest.h>
#include "../include/menu.h"

using namespace std;

void test1() { cout << "1"; return;};
void test2() { cout << "2"; return;};
void test3() { cout << "3"; return;};
void test4() { cout << "4"; return;};

TEST(menu, construtor){
    try {
        MenuSelelect m1("This is a fun1", &test1);
        MenuSelelect m2("This is a fun2", &test2);
        MenuSelelect m3("This is a fun3", &test3);
        MenuSelelect m4("This is a fun4", &test4);
        vector<Menu*> menu_sec_opt = {&m1, &m2};
        MenuOptions menu_sec = {"Menu Secundário", menu_sec_opt};
        vector<Menu*> menu_princ_opt = {&menu_sec, &m3, &m4};
        MenuOptions menu_princ("Menu Primário", menu_princ_opt);
        menu_princ.show();
    }
    catch(...) {
        EXPECT_EQ(true, false);
    }
}

/*
TEST(menu, input){
    MenuSelelect m1("Mensagem", )
    MenuOptions m2("Mensagem", )
    Menu
    MenuOptions m3("Mensagem", )
}*/
