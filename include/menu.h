#ifndef FEUP_AEDA_PROJ1_MENU_H
#define FEUP_AEDA_PROJ1_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "utilities.h"
using namespace std;

class Menu {
protected:
    string title;
public:
    Menu(string t) : title(t) {};
    const string get_title() const { return this->title;};
    void operator()() const{ this->show();};
    virtual void show() const = 0;
};

class MenuOptions : public Menu{
private:
    const vector<Menu*> options;
public:
    MenuOptions(string t, vector<Menu*> opt) : Menu(t), options(opt) {};
    friend ostream& operator<< (ostream &out, MenuOptions menu);
    void show() const override;
};

class MenuSelelect : public Menu{
private:
    void (*function)();
public:
    MenuSelelect(string title, void (*fun)()) : Menu(title) , function(fun) {};
    void show() const override;
};

//TODO Classe Login -> Select

#endif //FEUP_AEDA_PROJ1_MENU_H
