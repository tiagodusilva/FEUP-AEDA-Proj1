/** @file menu.h */
#ifndef FEUP_AEDA_PROJ1_MENU_H
#define FEUP_AEDA_PROJ1_MENU_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "exceptions.h"
#include "utilities.h"

/** @defgroup interface_grp Menu, GUI and interfacing module */

/** @addtogroup	interface_grp
  *
  * @brief	Code related to interfaces, menus and the application GUI
  *
  * @{
  */


/**
 * @brief	Absract class for menus that don't modify arguments
 */
class Menu {
protected:
	/** @brief	String inserted to std::cout on menu entering */
	std::string title;
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	Menu() = default;
	/**
	 * @brief	Default destructor
	 */
	virtual ~Menu() = default;
	/**
	 * @brief	Constructor for the Menu class
	 *
	 * @param t	String to be used as the Menu title
	 */
	Menu(std::string t) : title(t) {};

	/* GETTERS */
	/**
	 * @brief	Getter for the Menu title
	 *
	 * @return	Copy of the current Menu Title
	 */
	const std::string getTitle() const { return this->title; }

	/**
	 * @brief	Pure virtual member-function
	 * @note	Will be called when instancing a given menu
	 */
	virtual void show() = 0;
};


/**
 * @brief	Wrapper to a function that takes no arguments.
 */
class MenuSelect : public Menu{
private:
	/** @brief	Function that the menu calls when active */
	std::function<void()> func;
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MenuSelect() = default;
	/**
	 * @brief	Default destructor
	 */
	~MenuSelect() = default;
	/**
	 * @brief	Constructor for the MenuSelect class
	 *
	 * @param title	String to be used as the Menu title
	 * @param fun	Function to be called when the menu becomes active
	 */
	MenuSelect(std::string title, std::function<void()> fun) : Menu(title){ this->func = fun; }

	/**
	 * @brief	Call the function that the menu is pointing to
	 */
	void show() override { this->func(); utl::pauseConsole(); return; };
};


/**
 * @brief	Menu that serves as an interface to other MenuOption, MenuSelect or MenuFilter instances\n(all derived from menu)
 */
class MenuOptions : public Menu{
protected:
	/** @brief	List of menus that the current MenuOptions provides access to (options).\n
	 *		The order inside the vector is preserved
	 */
	std::vector<Menu*> options;
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MenuOptions() = default;
	/**
	 * @brief	Default destructor
	 */
	~MenuOptions() = default;
	/**
	 * @brief	Constructor for the MenuOptions class
	 *
	 * @param t	String to be used as the Menu title
	 * @param opt	List of menus this Menu is capable of calling/instantiate
	 */
	MenuOptions(std::string t, std::vector<Menu*> opt) : Menu(t), options(opt) {};

	/**
	 * @brief	Get current menu title followed by the title of each menu inside 'options'
	 *
	 * @return	String ready to be shown as the guide to the selection of available options
	 */
	std::string getMessage() const;

	/* INSERTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded ostream insertion operator
	 *
	 * @details	Mainly used with std::cout to show formated information on screen
	 *
	 * @param out	Reference to the ostream object to insert info to
	 * @param menu	Reference to the Menu object whose info will be inserted in the ostream
	 *
	 * @return	Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<< (std::ostream &out, const MenuOptions &menu) {
		out << menu.getMessage(); return out; };

	/**
	 * @brief	Invokes and displays all of the menus in options and waits for user input to call them
	 */
	void show() override;
};


/**
 * @brief	Abstract class used for specifying menus that modify an argument (by using different filters)
 *
 * @tparam Arg	Defines type of object that can be filtered (usually an, iterable, linear data structure)
 */
template<typename Arg>
class MenuFilter : public Menu{
public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MenuFilter<Arg>() = default;
	/**
	 * @brief	Default destructor
	 */
	virtual ~MenuFilter<Arg>() = default;
	/**
	 * @brief	Constructor for the MenuFilter class
	 *
	 * @param title	String to be used as the Menu title
	 */
	MenuFilter<Arg>(std::string title) : Menu(title) {}

	/** @brief	Invokes and displays all of the menus in options and waits for user input to call them */
	virtual void show(Arg&) = 0;
	/**
	 * @brief	Invokes and displays all of the menus in options and waits for user input to call them
	 */
	void show() override { return; };
};


/**
 * @brief	Wrapper to function that modifies an argument
 *
 * @tparam Arg	Defines type of object that can be filtered (usually an, iterable, linear data structure)
 */
template<typename Arg>
class MenuSelectFilter : public MenuFilter<Arg>{
private:
	/** @brief	Function that the menu calls when active\n
	 *		Takes an argument of type Arg
	 */
	std::function<void(Arg&)> func;

public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MenuSelectFilter<Arg>() = default;
	/**
	 * @brief	Default destructor
	 */
	~MenuSelectFilter<Arg>() = default;
	/**
	 * @brief	Constructor for the MenuSelectFilter class
	 *
	 * @param title	String to be used as the Menu title
	 * @param fun	Function that will called when the class is active
	 */
	MenuSelectFilter<Arg>(std::string title, std::function<void(Arg&)> fun) :
		MenuFilter<Arg>(title), func(fun) {};

	/**
	 * @brief	Invokes the data-member 'func' with the given argument, 'arg'
	 *
	 * @param arg	Argument to pass to the data-member 'func' as an argument
	 */
	void show(Arg &arg) override { this->func(arg); utl::pauseConsole(); }
};


/**
 * @brief	Menu that controls MenuSelectFilter and other MenuOptionsFilter
 *
 * @tparam Arg	Defines type of object that can be filtered (usually an, iterable, linear data structure)
 */
template<typename Arg>
class MenuOptionsFilter : public MenuFilter<Arg> {
private:
	/** @brief	Argument that is passed and modified */
	Arg argument;

	/* FUNCTIONS THAT WILL BE CALLED WHEN MENU IS STARTING/EXITING */
	/**
	 * @brief	Initialize to ensure that it points to something
	 *
	 * @return	A dead function
	 */
	std::function<Arg()> start_func = [](){ return Arg(); };
	/**
	 * @brief	Initialize to ensure that it points to something
	 *
	 * @return	A dead function
	 */
	std::function<void(Arg&)> exit_func = [](Arg){};

	/** @brief	List of menus that the current MenuOptionsFilter provides access to (filters).\n
	 *		The order inside the vector is preserved
	 */
	std::vector<MenuFilter<Arg>*> options;
	/** @brief	Backup of the vector 'options'\n
	 *		used when user can't select a menu more than once
	 */
	const std::vector<MenuFilter<Arg>*> options_backup;

	/** @brief	Specifies if only one menu from options can be chosen\n
	 *		Will exit from the menu when user selects any option
	 */
	bool select_one_menu;
	/**
	 * @brief	List of Menus that will be repeated
	 */
	const std::vector<int> repeat_menus_vec = {};

public:
	/* CONSTRUCTORS */
	/**
	 * @brief	Default constructor
	 */
	MenuOptionsFilter<Arg>() : MenuFilter<Arg>(), options_backup() {};
	/**
	 * @brief	Default destructor
	 */
	~MenuOptionsFilter<Arg>() = default;

	/**
	 * @brief	MenuOptionsFilter class constructor
	 *
	 * @warning	If repeated menus are given, they must be the first options in the options vector, 'opt'
	 *
	 * @param t			String to be used as the Menu title
	 * @param opt
	 * @param e_fun			Function that will called just before the class instance is destroyed
	 * @param s_fun			Function that will called when the class is instantiated
	 * @param exclusive_selection	Specifies if only one menu from options can be chosen
	 * @param menus_to_repeat	List of menus that will be repeated
	 */
	MenuOptionsFilter<Arg>(std::string t, std::vector<MenuFilter<Arg>*>opt,
			std::function<void(Arg&)> e_fun=[](Arg){  },
			std::function<Arg()>s_fun=[](){
				return(Arg());
			},
			bool exclusive_selection=false,
			std::vector<int> menus_to_repeat={  }) :
		MenuFilter<Arg>(t), options(opt), options_backup(opt),
		exit_func(e_fun), argument(s_fun()), start_func(s_fun),
		select_one_menu(exclusive_selection), repeat_menus_vec(menus_to_repeat){};

	/**
	 * @brief	Get current menu title followed by the title of each menu inside 'options'
	 *
	 * @return	String ready to be shown as the guide to the selection of available options
	 */
	std::string getMessage() const;

	/* INSERTION OPERATOR OVERLOAD */
	/**
	 * @brief	Overloaded ostream insertion operator
	 *
	 * @details	Mainly used with std::cout to show formated information on screen
	 *
	 * @param os	Reference to the ostream object to insert info to
	 * @param menu	Reference to the Menu object whose info will be inserted in the ostream
	 *
	 * @return	Reference to the ostream object, 'outstream', passed in the parameters
	 */
	friend std::ostream& operator<<(std::ostream &os, const MenuOptionsFilter<Arg> &menu){ os << menu.getMessage(); return os; }

	/** @brief	Instanciate menu with no initial value of arg */
	void show() override;
	/**
	 * @brief	Instanciate menu with a given arg
	 * @note	When calling any of its options, pass Arg as an argument to be modified
	 */
	void show(Arg&) override;
};


template<typename Arg>
void
MenuOptionsFilter<Arg>::show()
{
	/* If show() is called then the object was instanciated by a Menu_Options object */
	this->argument = start_func();	// Reinitialize argument
	this->options = options_backup;  // Reset all available options
	this->show(argument);
}


template<typename Arg>
void
MenuOptionsFilter<Arg>::show(Arg &arg)
{
	/* If show(Arg) is called then the object was instanciated by a MenuFilter object.
	   We will thus modify arg (by calling MenuFilters in the options vector)
	*/
	this->options = options_backup;  // Reset all available options

	bool go_back = false;
	do {
		if (options.size() == 0) // Don't run menu if there aren't any options
			go_back = true;
		else {
			utl::clearConsole();

			int selection = utl::getInt(std::cin, 0, options.size(),
					this->getMessage() + "Insira um numero entre 0 e "+ std::to_string(options.size()));
			if (selection == 0)
				if (this->options.size() == this->options_backup.size()) { // if the user hasn't selected any menu yet
					try {
						this->exit_func(arg);
					}catch(const std::exception &err) {
						std::cerr << err.what() << std::endl;
						utl::pauseConsole();
					}
					throw MenuExitWithNoFunctionCall(this->title);
				}
				else
					go_back = true;
			else {
				try {
					options.at(selection-1)->show(arg);
					/* Delete option if it isn't on the repeat vector */
					if (std::find(repeat_menus_vec.begin(), repeat_menus_vec.end(), selection-1) == repeat_menus_vec.end())
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
}


template<typename Arg>
std::string
MenuOptionsFilter<Arg>::getMessage() const
{
	std::string res="";
	res+= this->getTitle() + "\n\n";
	for (int i=0; i < options.size(); ++i)
		res += std::to_string(i+1) + "- " + options.at(i)->getTitle() + '\n';

	res += "0- Go back\n";
	return res;
}

/** @} */

#endif	// FEUP_AEDA_PROJ1_MENU_H
