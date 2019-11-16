#ifndef FILTER_H
#define FILTER_H

#include <algorithm>
#include <vector>
#include <string>

#include "address.h"
#include "enterprise.h"
#include "event.h"
#include "date.h"
#include "cards.h"
#include "museum.h"

using namespace std;

namespace flt
{
	/* CONTAINS */
	template<typename T>
	bool contains(const T &lhs, Address rhs) { return(lhs.get_address() == rhs); }

	template<typename T>
	bool contains(const T &lhs, string rhs) { return(lhs.get_name() == rhs); }

	template<typename T>
	bool contains(const T &lhs, Date rhs) { return(lhs.get_date() == rhs); }


	/* IS_BETWEEN */
	template<typename T>
	bool is_between(const T &mid, Date lhs, Date rhs) { return((mid.get_date() >= lhs) && (mid.get_date() <= rhs)); }


	/* FILTERS */

	void FilterEventByGivenTimeFrame(vector<Event> &vec, const Time &delta_time);
	void FilterEventByTimeFrame(vector<Event> &vec);
	void FilterEventByCapacity(vector<Event> &vec, float capacity_percentage_max);
	void FilterEventById(vector<Event> &vec);
	void FilterEventByLocationName(vector<Event> &vec);
	void FilterCardByName(vector<Card*> &vec);
	void FilterCardByValidity(vector<Card*> &vec);
	void FilterCardByInvalidity(vector<Card*> &vec);


	/* TEMPLATE FILTERS */
	template<typename T>
	void FilterByName(vector<T> &vec) {
		string name;
		cout << "Name?\n";
		getline(cin, name);

		/* move elements to remove to the end of vec */
		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&name](T &elem) {
					return!(contains(elem, name));
				});

		/* erase elements that were moved to the end of vec */
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterByEventID(vector<T> &vec) {
		unsigned event_id;
		cout << "Event id?\n";
		cin >> event_id;

		if(cin.fail())
			throw(UserInputReadingFailure("Invalid id"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&event_id](T &elem) { return!(elem.has_event(event_id)); });
		vec.erase(iter, vec.end());
	}


	template<typename T>
	void FilterByLocation(vector<T> &vec, Address addr) {
		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&addr](T &elem) { return!(contains(elem, addr)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterInDate(vector<T> &vec) {
		Date date;
		cout << "Date (year/month/day)?\n";
		cin >> date;

		if(cin.fail())
			throw(UserInputReadingFailure("Invalid date"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&date](T &elem) { return!(contains(elem, date)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterBetweenDates(vector<T> &vec) {
		Date date1;
		cout << "Date (year/month/day)?\n";
		cin >> date1;
		if(cin.fail())
			throw(UserInputReadingFailure("Invalid date"));

		Date date2;
		cout << "Date (year/month/day)?\n";
		cin >> date2;
		if(cin.fail())
			throw(UserInputReadingFailure("Invalid date"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&date1, &date2](T &elem) { return!(is_between(elem, date1, date2)); });
		vec.erase(iter, vec.end());
	}

	template<typename T>
	void FilterByLocationCin(vector<T> &vec) {
		Address addr;
		cout << "Address (street name/XXXX-XXX/region name  or  region)? ";
		cin >> addr;

		if(cin.fail())
			throw(UserInputReadingFailure("Invalid address"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&addr](T &elem) { return!(contains(elem, addr)); });
		vec.erase(iter, vec.end());
	}
}
#endif //FILTER_H
