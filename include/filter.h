#ifndef FILTER_CONTAINS_H
#define FILTER_CONTAINS_H

#include <algorithm>
#include <vector>
#include <string>

#include "address.h"
#include "event.h"
#include "date.h"
#include "cards.h"
#include "museum.h"

using namespace std;

namespace flt
{
	template<typename T>
	bool contains(const T &lhs, Address rhs) { return(lhs.get_address() == rhs); }

	template<typename T>
	bool contains(const T &lhs, string rhs) { return(lhs.get_name() == rhs); }

	template<typename T>
	bool contains(const T &lhs, Date rhs) { return(lhs.get_date() == rhs); }

	template<typename T>
	bool is_between(const T &mid, Date lhs, Date rhs) { return((mid.get_date() >= lhs) && (mid.get_date() <= rhs)); }

	template<typename T>
	void FilterByLocation(vector<T> &vec) {
		Address addr;
		cin >> addr;

		if(cin.fail())
			throw(NoSuchCard(123)); // TODO add exceptions for this

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&addr](T &elem) { return!(contains(elem, addr)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterByName(vector<T> &vec) {
		string name;
		getline(cin, name);

		if(cin.fail())
			throw(NoSuchCard(123)); // TODO add exceptions for this

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&name](T &elem) { return!(contains(elem, name)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterInDate(vector<T> &vec) {
		Date date;
		cin >> date;

		if(cin.fail())
			throw(NoSuchCard(123)); // TODO add exceptions for this

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&date](T &elem) { return!(contains(elem, date)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterBetweenDates(vector<T> &vec) {
		Date date1;
		cin >> date1;
		if(cin.fail())
			throw(NoSuchCard(123)); // TODO add exceptions for this

		Date date2;
		cin >> date2;
		if(cin.fail())
			throw(NoSuchCard(123)); // TODO add exceptions for this

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&date1, &date2](T &elem) { return!(is_between(elem, date1, date2)); });
		vec.erase(iter, vec.end());
	}
}
#endif //FILTER_CONTAINS_H
