#include "../include/filter.h"

using namespace std;

namespace flt
{
	/* For use with silver cards checker */
	void FilterEventByGivenTimeFrame(vector<Event> &vec, const Time &delta_time) {
		Date d_now; Time t_now;
		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&delta_time, &d_now, &t_now](Event elem) {
					if(d_now > elem.get_date())
						return true;
					else {
						/* Check if dates are the same but the event has already occurred */
						if(d_now == elem.get_date() && t_now > elem.get_time())
							return true;
						else {
							unsigned delta_in_seconds = delta_time.get_hour()*MIN_IN_HOUR + delta_time.get_min();
							return !(timespan_size(d_now, t_now, elem.get_date(), elem.get_time()) <= delta_in_seconds);
						}
					}
				});

		vec.erase(iter, vec.end());
	}

	void FilterEventByTimeFrame(vector<Event> &vec) {
		Time delta_time;
		cout << "Timeframe (hour:min)?\n";
		cin >> delta_time;

		if(cin.fail())
			throw(UserInputReadingFailure("Invalid timeframe"));

		Date d_now; Time t_now;
		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&delta_time, &d_now, &t_now](Event elem) {
					if(d_now > elem.get_date())
						return true;
					else {
						/* Check if dates are the same but the event has already occurred */
						if(d_now == elem.get_date() && t_now > elem.get_time())
							return true;
						else {
							unsigned delta_in_seconds = delta_time.get_hour()*MIN_IN_HOUR + delta_time.get_min();
							return !(timespan_size(d_now, t_now, elem.get_date(), elem.get_time()) <= delta_in_seconds);
						}
					}
				});
		vec.erase(iter, vec.end());

	}


	void FilterEventByCapacity(vector<Event> &vec, float capacity_percentage_max) {
		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&capacity_percentage_max](Event elem) {
					return !(elem.get_capacity_percentage() <= capacity_percentage_max*100);
				});

		vec.erase(iter, vec.end());
	}


	void FilterEventById(vector<Event> &vec) {
		unsigned event_id;
		cout << "Event id?\n";
		cin >> event_id;

		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&event_id](Event elem) { return!(elem.get_id() == event_id); });
		vec.erase(iter, vec.end());
	}


	void FilterEventByLocationName(vector<Event> &vec) {
		string location;
		cout << "Location Name?\n";
		getline(cin, location);

		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&location](Event &elem){ return !(elem.get_location_name() == location); });

		vec.erase(iter, vec.end());
	}


	void FilterCardByName(vector<Card*> &vec) {
		string name;
		cout << "Name?\n";
		getline(cin, name);

		vector<Card*>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&name](Card* &elem) {
					return !(elem->get_name() == name);
				});

		vec.erase(iter, vec.end());
	}


	void FilterCardByValidity(vector<Card*> &vec) {
		vector<Card*>::iterator iter = remove_if(vec.begin(), vec.end(),
				[](Card* elem) {
					return!(elem->isvalid());
				});

		vec.erase(iter, vec.end());
	}


	void FilterCardByInvalidity(vector<Card*> &vec) {
		vector<Card*>::iterator iter = remove_if(vec.begin(), vec.end(),
				[](Card* elem) { return(elem->isvalid()); });
		vec.erase(iter, vec.end());
	}
}
