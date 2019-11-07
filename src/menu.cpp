#include "../include/menu.h"

using namespace std;

string MenuOptions::getMessage() const{
	string res="";
    res+= getTitle() + "\n\n";
    for (int i=0; i < options.size(); ++i){
        res += to_string(i+1) + "- " + options.at(i)->getTitle() + '\n';
	}
    res += "0- Go back\n";
    return res;
}

void MenuOptions::show() {
    bool go_back = false;

    do{
        int selection = utl::getInt(cin, 0, options.size(), this->getMessage() + "Insira um numero entre 0 e " + to_string(options.size()));
        if(selection == 0)
            go_back = true;
        else
			try {
				options.at(selection - 1)->show();

			} catch(const MenuExitWithNoFunctionCall &err) {
				// ignore if a menu exits without calling anything
			} catch(const exception &err) {
				cerr << err.what();
			}
    } while (!go_back);

    return;
}
