#include "../include/menu.h"

using namespace std;

string MenuOptions::getMessage() const {
	string res; // No need to initialize (it would be redundant)
	res+= getTitle() + "\n\n";

	for (size_t i=0; i < options.size(); ++i){
		res += to_string(i+1) + "- " + options.at(i)->getTitle() + '\n';
	}

	res += "0- Go back\n";
	return res;
}

void MenuOptions::show() {
    bool go_back = false;

    do{
	utl::clearConsole();
        int selection = utl::getInt(cin, 0, options.size(), this->getMessage() + "Insira um numero entre 0 e " + to_string(options.size()));

        if(selection == 0 || options.empty())
            go_back = true;
        else
		try {
			options.at(selection-1)->show();

		} catch(const MenuForceExit &err) {
			cout << err.what() << endl;
			return;

		} catch(const MenuExitWithNoFunctionCall &err) {
			// ignore if a menu exits without calling anything

		} catch(const std::exception &err) {
			cerr << err.what() << endl;
			utl::pauseConsole();
		}
    } while (!go_back);

}
