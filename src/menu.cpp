#include "../include/menu.h"

using namespace std;

ostream& operator<< (ostream &os, MenuOptions menu){
    os << menu.get_title() << endl << endl;
    for (int i = 0; i < menu.options.size(); ++i)
        os << i+1 << "- " << menu.options.at(i)->get_title() << endl;
    os << "0- Go back" << endl;
    return os;
}

void MenuOptions::show() const {
    bool go_back = false;

    do{
        cout << *this;
        int selection = utl::getInt(cin, 0, options.size(), "Insira um numero entre 0 e " + to_string(options.size()));
        if(selection == 0)
            go_back = true;
        else
            options.at(selection - 1)->show();
    } while (!go_back);

    return;
}

void MenuSelelect::show() const {
    this->function();
    utl::pauseConsole();
}
