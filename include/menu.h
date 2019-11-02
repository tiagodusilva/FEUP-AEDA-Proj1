#ifndef FEUP_AEDA_PROJ1_MENU_H
#define FEUP_AEDA_PROJ1_MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "utilities.h"

class Menu {
protected:
    std::string title;
public:
    Menu(std::string t) : title(t) {};
    const std::string get_title() const { return this->title;};
    void operator()() const{ this->show();};
    virtual void show() const = 0;
};

class MenuOptions : public Menu{
private:
    const std::vector<Menu*> options;
public:
    MenuOptions(std::string t, std::vector<Menu*> opt) : Menu(t), options(opt) {};
    friend std::ostream& operator<< (std::ostream &out, MenuOptions menu);
    void show() const override;
};


class MenuSelelect : public Menu{
private:
    void (*function)();
public:
    MenuSelelect(std::string title, void (*fun)()) : Menu(title) , function(fun) {};
    void show() const override;
};

//TODO Classe Login -> Select

#endif //FEUP_AEDA_PROJ1_MENU_H
