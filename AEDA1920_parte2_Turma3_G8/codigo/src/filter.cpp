#include "../include/filter.h"

using namespace std;

namespace flt
{
	/* For use with silver cards checker */
	void FilterEventByGivenTimeFrame(vector<Event> &vec, const unsigned delta_time_hour, const unsigned delta_time_min) {
		Date d_now; Time t_now;
		if (delta_time_hour < 0 || delta_time_min < 0)
			throw InvalidObject("Time:", "Invalid Timeframe (neither hours, nor minutes can be negative)");

		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&delta_time_hour, &delta_time_min, &d_now, &t_now](Event elem) {
					if (d_now > elem.get_date())
						return true;
					else {
						/* Check if dates are the same but the event has already occurred */
						if (d_now == elem.get_date() && t_now > elem.get_time())
							return true;
						else {
							unsigned delta_in_seconds = delta_time_hour * MIN_IN_HOUR + delta_time_min;
							return !(timespan_size(d_now, t_now, elem.get_date(), elem.get_time()) <= delta_in_seconds);
						}
					}
				});

		vec.erase(iter, vec.end());
	}

	void FilterEventByTimeFrame(vector<Event> &vec) {
		string temp_time;
		cout << "Timeframe (hour:min)?\n";
		getline(std::cin, temp_time);

		int div = temp_time.find(':');
		if (div == string::npos)
			throw UserInputReadingFailure("Invalid Timeframe: input is malformed");

		unsigned delta_time_hour = stoi(temp_time.substr(0, div));
		unsigned delta_time_min = stoi(temp_time.substr(div + 1));

		if (delta_time_hour < 0 || delta_time_min < 0)
			throw UserInputReadingFailure("Invalid Timeframe: neither hours, nor minutes can be negative");

		Date d_now; Time t_now;
		vector<Event>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&delta_time_hour, &delta_time_min, &d_now, &t_now](Event elem) {
					if(d_now > elem.get_date())
						return true;
					else {
						/* Check if dates are the same but the event has already occurred */
						if(d_now == elem.get_date() && t_now > elem.get_time())
							return true;
						else {
							unsigned delta_in_seconds = delta_time_hour * MIN_IN_HOUR + delta_time_min;
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

	void FilterRepairEnterprisesByCoordinates(vector<RepairEnterprise> &vec,
			tuple<float, float> coord, float distance)
	{
		vector<RepairEnterprise>::iterator iter = remove_if(vec.begin(), vec.end(),
				[&distance, &coord](RepairEnterprise elem) {
					return(utl::coord_dist(elem.get_coords(), coord) > distance);
				});
		vec.erase(iter, vec.end());

	}

	void FilterWorkersByEmployment(vector<StateWorker> &vec) {
		vector<StateWorker>::iterator iter = remove_if(vec.begin(), vec.end(),
				[](StateWorker elem) { return(!elem.ishired()); });
		vec.erase(iter, vec.end());
	}


	void FilterWorkersByNonEmployment(vector<StateWorker> &vec) {
		vector<StateWorker>::iterator iter = remove_if(vec.begin(), vec.end(),
				[](StateWorker elem) { return(elem.ishired()); });
		vec.erase(iter, vec.end());
	}
}
