#ifndef FEUP_AEDA_PROJ1_MENU_H
#define FEUP_AEDA_PROJ1_MENU_H

#include <algorithm>
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
	/* Constructors */
	Menu() = default;
	virtual ~Menu() = default;
    Menu(std::string t) : title(t) {};

    const std::string getTitle() const { return this->title;};

	/* TODO Maybe delete () idk yet */
    void operator()() { this->show();};

	/* Show function that will be called when instancing a given menu */
    virtual void show() = 0;
};


// Wrapper to a function that takes no arguments.
class MenuSelelect : public Menu{
private:
	std::function<void()> func;
public:
	MenuSelelect() = default;
	~MenuSelelect() = default;
    MenuSelelect(std::string title, std::function<void()> fun) : Menu(title){ this->func = fun; };

	/* Call the function that the menu is pointing to */
    void show() override { this->func(); utl::pauseConsole(); return; };
};


// Menu that serves as an interface to other MenuOption, MenuSelelect or MenuFilter instances (all derived from menu).
class MenuOptions : public Menu{
protected:
    std::vector<Menu*> options;
public:
	MenuOptions() = default;
	~MenuOptions() = default;
    MenuOptions(std::string t, std::vector<Menu*> opt) : Menu(t), options(opt) {};

	std::string getMessage() const;

    friend std::ostream& operator<< (std::ostream &out, MenuOptions menu) { out << menu.getMessage(); return out; };

	/* Invokes and displays all of the menus in options and waits for user input to call them */
    void show() override;
	/* Exits gracefully from the menu */
};


template<typename Arg> // Abstract class used for specifyiing menus that modify an argument (by using different filters)
class MenuFilter : public Menu{
public:
	MenuFilter<Arg>() = default;
	virtual ~MenuFilter<Arg>() = default;
	MenuFilter<Arg>(std::string title) : Menu(title) {};

	/* same as show() from Menu but that takes a reference to an argument */
	virtual void show(Arg&) = 0;
    void show() override { return; };
};


template<typename Arg> // Wrapper to function that modifies an argument
class MenuSelelectFilter : public MenuFilter<Arg>{
private:
	std::function<void(Arg&)> func;

public:
	MenuSelelectFilter<Arg>() = default;
	~MenuSelelectFilter<Arg>() = default;
    MenuSelelectFilter<Arg>(std::string title, std::function<void(Arg&)> fun) : MenuFilter<Arg>(title), func(fun) {};

    void show(Arg &arg) override { this->func(arg); utl::pauseConsole(); return; };
};


template<typename Arg> // Menu that controls MenuSelelectFilter and other MenuOptionsFilter (all derived from MenuFilter)
class MenuOptionsFilter : public MenuFilter<Arg>{
private:
	/* Argument that is passed and modified */
	Arg argument;

	/* Functions that will be called when menu is starting/exiting. */
	std::function<Arg()> start_func = [](){return Arg();}; // Initialize as a dead function to ensure that it points to something
	std::function<void(Arg&)> exit_func = [](Arg){ return;}; // Initialize as a dead function to ensure that it points to something

    std::vector<MenuFilter<Arg>*> options;
	/* Backup vector (used when user can't select a menu more than once). */
    const std::vector<MenuFilter<Arg>*> options_backup;

	/* Specifies if only one menu from options can be chosen (will exit from the menu when user selects any option) */
	bool select_one_menu;
	/* Specifies if the same menu can be selected more than once (when a user selects an option it won't be deleted) */
	const std::vector<int> repeat_menus_vec ={};

public:
	MenuOptionsFilter<Arg>() : MenuFilter<Arg>(), options_backup() {};
	~MenuOptionsFilter<Arg>() = default;
	/* Warnning! If repeated menus are give, they must be the first options in the options vector */
	MenuOptionsFilter<Arg>(std::string t, std::vector<MenuFilter<Arg>*>opt, std::function<void(Arg&)> e_fun=[](Arg){return;},
		std::function<Arg()>s_fun=[](){ return(Arg()); }, bool exclusive_selection=false, std::vector<int> vec={}):
		MenuFilter<Arg>(t), options(opt), options_backup(opt), exit_func(e_fun), argument(s_fun()), start_func(s_fun),
		select_one_menu(exclusive_selection), repeat_menus_vec(vec){};

	/* Returns the menu select message */
	std::string getMessage() const;

    friend std::ostream& operator<<(std::ostream &os, const MenuOptionsFilter<Arg> menu){ os << menu.getMessage(); return os; }

	/* Instanciate menu with no initial value of arg. */
	void show() override;
	/* Instanciate menu with a given arg. When calling any of its options, pass Arg as an argument to be modified. */
	void show(Arg&) override;
};

template<typename Arg>
void MenuOptionsFilter<Arg>::show(){
	/* If show() is called then the object was instanciated by a Menu_Options object */
	this->argument = start_func(); // Reinitialize argument
	this->options = options_backup; // Reset all available options
	this->show(argument);
    return;
}

template<typename Arg>
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
					this->getMessage() + "Insira um numero entre 0 e "+ std::to_string(options.size()));
			if(selection == 0)
				if(this->options.size() == this->options_backup.size()) { // if the user hasn't selected any menu yet
					try {
						this->exit_func(arg);
					}catch(const std::exception &err) {
						std::cerr << err.what() << std::endl;
						utl::pauseConsole();
					}
					throw(MenuExitWithNoFunctionCall(this->title));
				}
				else
					go_back = true;
			else {
				try {
					options.at(selection-1)->show(arg);
					/* Delete option if it isn't on the repeat vector */
					if(std::find(repeat_menus_vec.begin(), repeat_menus_vec.end(), selection-1) == repeat_menus_vec.end())
						options.erase(options.begin() + (selection-1));
				}catch(const std::exception &err) {
					std::cerr << err.what() << std::endl;
					utl::pauseConsole();
				}
			}
		}
	} while (!go_back && !select_one_menu);

	utl::clearConsole();

	try {
		this->exit_func(arg);
	}catch(const std::exception &err) {
		std::cerr << err.what() << std::endl;
		utl::pauseConsole();
	}

    return;
}

template<typename Arg>
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
