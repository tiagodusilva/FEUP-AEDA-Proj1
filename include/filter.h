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
#include "stateworker.h"
#include "repairenterprise.h"
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
	 * @brief	Remove elements from given vector, 'vec', that will take place more than a given time from now (or have already taken place)
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *
	 * @param vec			Vector that contains the elements to evaluate
	 * @param delta_time_hour	Maximum	time difference (in hours and minutes) that an Event can have from now
	 * @param delta_time_min	Minimum	time difference (in hours and minutes) that an Event can have from now
	 */
	void FilterEventByGivenTimeFrame(vector<Event> &vec, const unsigned delta_time_hour, const unsigned delta_time_min);
	/**
	 * @brief	Remove elements from given vector, 'vec', that will take place more than a given time from now (or have already taken place)
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object).
	 *		The maximum time difference is given by the user (thorugh std::cin)
	 *
	 * @param vec		Vector that contains the elements to evaluate
	 */
	void FilterEventByTimeFrame(vector<Event> &vec);
	/**
	 * @brief	Remove elements from given vector, 'vec', that have at least a certain percentage of their capacity full
	 * @note	The given object has to have a 'get_capacity_percentage' public member-function (that returns a float)
	 *
	 * @param vec				Vector that contains the elements to evaluate
	 * @param capacity_percentage_max	Maximum	capacity an event can have before being filtered
	 */
	void FilterEventByCapacity(vector<Event> &vec, float capacity_percentage_max);
	/**
	 * @brief	Remove elements from given vector, 'vec', that match the given ID
	 * @note	The given object has to have a 'get_id' public member-function (that returns an unsigned integer).
	 *		The ID to match is read from the user (thorugh std::cin)
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterEventById(vector<Event> &vec);
	/**
	 * @brief	Remove elements from given vector, 'vec', that take place at a given location
	 * @note	The given object has to have a 'get_location_name' public member-function (that returns a String)
	 *		The location to look for is given by the user (thorugh std::cin)
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterEventByLocationName(vector<Event> &vec);
	/**
	 * @brief	Remove elements from given vector, 'vec', that have a given name
	 * @note	The given object has to have a 'get_name' public member-function (that returns a String)
	 *		The location to look for is given by the user (thorugh std::cin)
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterCardByName(vector<Card*> &vec);
	/**
	 * @brief	Remove elements from given vector, 'vec', that are valid
	 * @note	The given object has to have a 'isvalid' public member-function (that returns a bool)
	 *		The bool to matcg is 'true'
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterCardByValidity(vector<Card*> &vec);
	/**
	 * @brief	Remove elements from given vector, 'vec', that are invalid
	 * @note	The given object has to have a 'isvalid' public member-function (that returns a bool)
	 *		The bool to matcg is 'false'
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterCardByInvalidity(vector<Card*> &vec);

	/**
	 * @brief	Removes all RepairEnterprises in the given vector which distance to a given point
	 *	surpasses a given maximum distance
	 *
	 * @param vec	Vector to be filtered
	 * @param coord	Coordiantes of the point
	 * @param distance	Maximum distance between the given point and each of the RepairEnterprises
	 */
	void FilterRepairEnterprisesByCoordinates(vector<RepairEnterprise> &vec, tuple<float, float> coord, float distance);
	/**
	 * @brief	Remove all workers present in the given vector that aren't employed by the network:
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterWorkersByEmployment(vector<StateWorker> &vec);

	/**
	 * @brief	Remove all workers present in the given vector that are being employed by the network.
	 *
	 * @param vec	Vector that contains the elements to evaluate
	 */
	void FilterWorkersByNonEmployment(vector<StateWorker> &vec);

	/* TEMPLATE SORTS */
	/**
	 * @brief	Sort elements from given vector, 'vec', that have a given name
	 * @note	The given object has to have a 'get_name' public member-function (that returns a String)
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to sort
	 */
	template<typename T>
	void SortByName(vector<T> &vec) {
		sort(vec.begin(), vec.end(),
			[](T &elem1, T &elem2) {
				return elem1.get_name() < elem2.get_name();
			});
	}

	/**
	 * @brief	Sort elements from given vector, 'vec', that have a given location name
	 * @note	The given object has to have a 'get_location_name' public member-function (that returns a String)
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to sort
	 */
	template<typename T>
	void SortByLocation(vector<T> &vec) {
		sort(vec.begin(), vec.end(),
				[](T &elem1, T &elem2) { return elem1.get_location_name() < elem2.get_location_name(); });
	}

	/* TEMPLATE FILTERS */
	/**
	 * @brief	Remove elements from given vector, 'vec', that have a given name
	 * @note	The given object has to have a 'get_name' public member-function (that returns a String)
	 *		The location to look for is given by the user (thorugh std::cin)
	 *
	 * @warning	Uses the 'contains' set of functions
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 */
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
	/**
	 * @brief	Remove elements from given vector, 'vec', that match the given ID
	 * @note	The given objects have to have a 'has_event' public member-function (that returns a bool).
	 *		The ID to match is read from the user (thorugh std::cin)
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 */
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
	/**
	 * @brief	Remove elements from given vector, 'vec', that take place at a given location
	 * @note	The given object has to have a 'get_location_name' public member-function (that returns a String)
	 *		The location to look for is given by the user (thorugh std::cin)
	 *
	 * @warning	Uses the 'contains' set of functions
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 * @param addr	Address to match
	 */
	template<typename T>
	void FilterByLocation(vector<T> &vec, Address addr) {
		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&addr](T &elem) { return!(contains(elem, addr)); });
		vec.erase(iter, vec.end());
	}
	/**
	 * @brief	Remove elements from given vector, 'vec', that take place at a given date
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *		The Date to compare with is given by the user (thorugh std::cin)
	 *
	 * @warning	Uses the 'contains' set of functions
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 */
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
	/**
	 * @brief	Remove elements from given vector, 'vec', that take place between 2 dates
	 * @note	The given object has to have a 'get_date' public member-function (that returns a Date object)
	 *		The Dates to compare with are given by the user (thorugh std::cin)
	 *
	 * @warning	Uses the 'contains' set of functions
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 */
	template<typename T>
	void FilterBetweenDates(vector<T> &vec) {
		Date date1;
		cout << "Start date (year/month/day)?\n";
		cin >> date1;
		if(cin.fail())
			throw(UserInputReadingFailure("Invalid date"));

		Date date2;
		cout << "End date (year/month/day)?\n";
		cin >> date2;
		if(cin.fail())
			throw(UserInputReadingFailure("Invalid date"));

		typename vector<T>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&date1, &date2](T &elem) { return!(is_between(elem, date1, date2)); });
		vec.erase(iter, vec.end());
	}
	/**
	 * @brief	Remove elements from given vector, 'vec', that take place at a given Address
	 * @note	The given object has to have a 'get_address' public member-function (that returns a Address object)
	 *		The Address to match is given by the user (thorugh std::cin)
	 *
	 * @warning	Uses the 'contains' set of functions
	 *
	 * @tparam T	Object type of the elements to match
	 * @param vec	Vector that contains the elements to evaluate
	 */
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
