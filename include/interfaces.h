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

class GUI {
private:
	MuseumNetwork museum_network;

public:
	GUI() = default;
	~GUI() = default;
	void show();
};

class AdminInterface {
private:
	MuseumNetwork museum_network;

public:
	AdminInterface(MuseumNetwork &rnm) : museum_network(rnm) {};
	AdminInterface() = default;
	~AdminInterface() = default;
	void show() { return; };
};


class UserInterface {
private:
	MuseumNetwork &museum_network;

public:
	~UserInterface() = default;
	UserInterface(MuseumNetwork &rnm);
	void show();
};


class MemberInterface {
private:
	MuseumNetwork &museum_network;
	Card *member_card;

public:
//	MemberInterface() = default;
	~MemberInterface() = default;
	MemberInterface(MuseumNetwork &rnm, unsigned int cc);
	void show();
};

#endif	// INTERFACES_H
