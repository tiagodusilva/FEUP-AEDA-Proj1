#ifndef FEUP_AEDA_PROJ1_MENU_H
#define FEUP_AEDA_PROJ1_MENU_H
#define BAZINGA template

#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "exceptions.h"
#include "utilities.h"


// Absract class for menus that don't modify arguments
class Menu {
protected:
    std::string title;
public:
	Menu() = default;
    Menu(std::string t) : title(t) {};
    const std::string getTitle() const { return this->title;};
    void operator()() { this->show();};
    virtual void show() = 0;
};


// Wrapper to a function that takes no arguments.
class MenuSelelect : public Menu{
private:
	std::function<void()> func;
public:
    MenuSelelect(std::string title, std::function<void()> fun) : Menu(title){ this->func = fun; };
    void show() override { this->func(); utl::pauseConsole(); utl::ignore(std::cin); return; };
};


// Menu that serves as an interface to other MenuOption, MenuSelelect or MenuFilter instances (all derived from menu).
class MenuOptions : public Menu{
protected:
    std::vector<Menu*> options;
public:
	MenuOptions() : Menu() { options.clear(); };
    MenuOptions(std::string t, std::vector<Menu*> opt) : Menu(t), options(opt) {};
	std::string getMessage() const;
    friend std::ostream& operator<< (std::ostream &out, MenuOptions menu) { out << menu.getMessage(); return out; };
    void show() override;
};


BAZINGA<typename Arg> // Abstract class used to modify an argument (by using different filters)
class MenuFilter : public Menu{
public:
	MenuFilter<Arg>() : Menu() {};
	MenuFilter<Arg>(std::string title) : Menu(title) {};
	virtual void show(Arg&) = 0;
    void show() override { return; };
};


BAZINGA<typename Arg> // Wrapper to function that modifies an argument
class MenuSelelectFilter : public MenuFilter<Arg>{
private:
	std::function<void(Arg&)> func;
public:
    MenuSelelectFilter<Arg>(std::string title, std::function<void(Arg&)> fun) : MenuFilter<Arg>(title){ this->func = fun; };
    void show(Arg &arg) override { this->func(arg); utl::pauseConsole(); utl::ignore(std::cin); return; };
};


BAZINGA<typename Arg> // Menu that controls MenuSelelectFilter and other MenuOptionsFilter (all derived from MenuFilter)
class MenuOptionsFilter : public MenuFilter<Arg>{
private:
	Arg argument;
    std::vector<MenuFilter<Arg>*> options;
    const std::vector<MenuFilter<Arg>*> options_backup; // Store options in a backup vector (used when menus are one time run).
	std::function<void(Arg&)> exit_func = [](Arg){ return;}; // Initialize exit_func as a dead function to ensure that it points to something
	bool select_one_menu; // Specifies if only one menu can be chosen
	bool repeat_menus; // Specifies if menus in options are run only once
public:
	MenuOptionsFilter<Arg>(std::string t, std::vector<MenuFilter<Arg>*>opt, std::function<void(Arg&)> e_fun=[](Arg){return;}, bool exclusive_selection=false, bool repeat=false)
		: MenuFilter<Arg>(t), options(opt), options_backup(opt), exit_func(e_fun),select_one_menu(exclusive_selection), repeat_menus(repeat){};

	std::string getMessage() const;
	void show() override;
	void show(Arg&) override;
    friend std::ostream& operator<<(std::ostream &os, const MenuOptionsFilter<Arg> menu){ os << menu.getMessage(); return os; }
};

BAZINGA<typename Arg>
void MenuOptionsFilter<Arg>::show(){
	/* If show() is called then the object was instanciated by a Menu_Options object */
	this->argument = Arg(0); // Reinitialize argument
	this->options = options_backup; // Reset all available options
	this->show(argument);
    return;
}

BAZINGA<typename Arg>
void MenuOptionsFilter<Arg>::show(Arg &arg){ // handles kbc interrupts
	/* If show(Arg) is called then the object was instanciated by a MenuFilter object.
	   We will thus modify arg (by calling MenuFilters in the options vector)
	*/

    bool go_back = false;
    do{
		if(options.size() == 0) // Don't run menu if there aren't any options
			go_back=true;
		else {
			utl::clearConsole();

			int selection = utl::getInt(std::cin, 0, options.size(),
					this->getMessage() + "Insira um numero entre 0 e "); //+ to_string(options.size());
			if(selection == 0)
				//if(this->options.size() == this->options_backup.size()) // if the user hasn't selected any menu yet
						if(this->options.size() == this->options_backup.size()) // if the user hasn't selected any menu yet
					throw(MenuExitWithNoFunctionCall(this->title));
				else
					go_back = true;
			else {
				try {
					options.at(selection-1)->show(arg);
					if(!repeat_menus)
						options.erase(options.begin() + (selection-1));
				}catch(const std::exception &err) {
					std::cerr << err.what();
				}
			}
		}
	} while (!go_back && !select_one_menu);

	utl::clearConsole();

	try {
		this->exit_func(arg);
	}catch(const std::exception &err) {
		std::cerr << err.what();
	}

    return;
}

BAZINGA<typename Arg>
std::string MenuOptionsFilter<Arg>::getMessage() const{
	std::string res="";
    res+= this->getTitle() + "\n\n";
    for (int i=0; i < options.size(); ++i)
        res += std::to_string(i+1) + "- " + options.at(i)->getTitle() + '\n';
    res += "0- Go back\n";
    return res;
}


//TODO Classe Login -> Select

#endif //FEUP_AEDA_PROJ1_MENU_H
