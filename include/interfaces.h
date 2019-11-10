#ifndef INTERFACES_H
#define INTERFACES_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "cards.h"
#include "filter_contains.h"
#include "menu.h"
#include "museum_network.h"


class AdminInterface {
private:
	MuseumNetwork museum_network;
public:
	AdminInterface(MuseumNetwork &rnm);
	AdminInterface() = default;
	~AdminInterface() = default;
};


class UserInterface {
private:
	MuseumNetwork museum_network;
public:
	UserInterface(MuseumNetwork &rnm);
	UserInterface() = default;
	~UserInterface() = default;
};


class MemberInterface {
private:
	MuseumNetwork museum_network;
	Card *member_card;

public:
	MemberInterface() = default;
	~MemberInterface() = default;
	MemberInterface(MuseumNetwork &rnm, unsigned int cc);
	void show();
};

#endif	// INTERFACES_H
