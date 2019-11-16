/** @file filter.h */
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

/** @brief	General filtering functions */
namespace flt
{
	/* CONTAINS */
	/**
	 * @brief	Check if a given object contains a given Address object
	 * @note	The given object has to have a 'get_address' public member-function (that returns an Address object)
	 *
	 * @tparam T	Type of the object to get the comparison Address from
	 * @param lhs	Object to get the comparison Address from
	 * @param rhs	Address to compare the given object's Address to
	 *
	 * @return	true, if both Addresses are considered equal,\n
	 *		false, otherwise
	 */
	template<typename T>
	bool contains(const T &lhs, Address rhs) { return(lhs.get_address() == rhs); }

	/**
	 * @brief	Check if a given object contains a given name (String)
	 * @note	The given object has to have a 'get_name' public member-function (that returns a String)
	 *
	 * @tparam T	Type of the object to get the comparison name String from
	 * @param lhs	Object to get the comparison name String from
	 * @param rhs	String to compare the given object's name String to
	 *
	 * @return	true, if both names are considered equal,\n
	 *		false, otherwise
	 */
	template<typename T>
	bool contains(const T &lhs, string rhs) { return(lhs.get_name() == rhs); }

	/**
	 * @brief	Check if a given object contains a given Date object
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *
	 * @tparam T	Type of the object to get the comparison Date from
	 * @param lhs	Object to get the comparison Date from
	 * @param rhs	Date to compare the given object's Date to
	 *
	 * @return	true, if both Date are considered equal,\n
	 *		false, otherwise
	 */
	template<typename T>
	bool contains(const T &lhs, Date rhs) { return(lhs.get_date() == rhs); }


	/**
	 * @brief	Check if a given object's Date is chronologically between 2 other Date objects
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *
	 * @tparam T	Type of the object to get the comparison Date from
	 * @param mid	Object to get the comparison Date from (one that is chronologically between the other 2)
	 * @param lhs	Date to compare as taking place before mid
	 * @param rhs	Date to compare as taking place after mid
	 *
	 * @return	true, if a given object's Date ('mid's date) is chronologically between 2 other Date objects [lhs, rhs]\n
	 *		false, otherwise
	 */
	template<typename T>
	bool is_between(const T &mid, Date lhs, Date rhs) { return((mid.get_date() >= lhs) && (mid.get_date() <= rhs)); }


	/* FILTERS */
	/**
	 * @brief	Remove elements from given vector, 'vec', that will take place more than a given time from now
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *
	 * @param vec		Vector that contains the elements to evaluate
	 * @param delta_time	Maximum
	 */
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
		cout << "Address (street name/XXXX-XXX/region name  or	region)? ";
		cin >> addr;

		if(cin.fail())
			throw(UserInputReadingFailure("Invalid address"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&addr](T &elem) { return!(contains(elem, addr)); });
		vec.erase(iter, vec.end());
	}
}
#endif //FILTER_H
