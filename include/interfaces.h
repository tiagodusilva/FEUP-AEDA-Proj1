/** @file interfaces.h */
#ifndef INTERFACES_H
#define INTERFACES_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cards.h"
#include "filter.h"
#include "menu.h"
#include "museum_network.h"

/** @addtogroup	interface_grp
  * @{
  */


/** @brief	Application's active class */
class GUI {
private:
	/** @brief	Reference to MuseumNetwork that GUI is currently interfacing */
	MuseumNetwork &museum_network;

public:
	/**
	 * @brief	GUI constructor
	 *
	 * @param rnm	Reference to the MuseumNetwork that will be handled by this GUI instance
	 */
	GUI(MuseumNetwork &rnm) : museum_network(rnm) {};
	/** @brief	GUI default destructor */
	~GUI() = default;
	/** @brief	Method called when the GUI is instanciated */
	void show();
};


/** @brief	Interface instanciated when an ADMIN signs in */
class AdminInterface {
private:
	/** @brief	Reference tho the MuseumNetwork currently being handled by the GUI */
	MuseumNetwork &museum_network;

public:
	/**
	 * @brief	Constructor for the AdminInterface
	 *
	 * @param rnm	Reference to the MuseumNetwork to work with
	 */
	AdminInterface(MuseumNetwork &rnm);
	/** @brief	AdminInterface default destructor */
	~AdminInterface() = default;
	/** @brief	Method called when the AdminInterface is instanciated */
	void show();
};


/** @brief	Interface instanciated when a NON-REGISTERED user signs in */
class UserInterface {
private:
	/** @brief	Reference tho the MuseumNetwork currently being handled by the GUI */
	MuseumNetwork &museum_network;

public:
	/**
	 * @brief	Constructor for the UserInterface (non-registered user)
	 *
	 * @param rnm	Reference to the MuseumNetwork to work with
	 */
	UserInterface(MuseumNetwork &rnm);
	/** @brief	UserInterface default destructor */
	~UserInterface() = default;
	/** @brief	Method called when the UserInterface is instanciated */
	void show();
};


/** @brief	Interface instanciated when a MEMBER signs in */
class MemberInterface {
private:
	/** @brief	Reference tho the MuseumNetwork currently being handled by the GUI */
	MuseumNetwork &museum_network;
	/** @brief	Pointer to the currently signed in member's Card */
	Card *member_card;

public:
	/**
	 * @brief	Constructor for the MemberInterface (registered user)
	 *
	 * @param rnm	Reference to the MuseumNetwork to work with
	 * @param cc	CC of the user that's attempting to sign-in
	 */
	MemberInterface(MuseumNetwork &rnm, unsigned int cc);
	/** @brief	MemberInterface default destructor */
	~MemberInterface() = default;
	/** @brief	Method called when the MemberInterface is instanciated */
	void show();
};

/** @} */

#endif	// INTERFACES_H
