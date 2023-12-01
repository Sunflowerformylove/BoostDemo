// Description: This file contains the functions for the Chrono class.
// Both chrono class and date_time class are used in this file.
#include "Chrono.h"

int month_string_to_int(string month)
{
	for(int i = 0; i < 12; i++)
	{
		if(month == MONTHS[i])
		{
			return i + 1;
		}
	}
	return -1;
}

string get_current_time()
{
	ptime now = second_clock::local_time();
	date gregorian_day = now.date();
	string date;
	date += gregorian_day.day_of_week().as_long_string();
	date += ", ";
	date += to_string(gregorian_day.day());
	date += " ";
	date += gregorian_day.month().as_long_string();
	date += " ";
	date += to_string(gregorian_day.year());
	date += " ";
	date += to_string(now.time_of_day().hours());
	date += ":";
	date += to_string(now.time_of_day().minutes());
	date += ":";
	date += to_string(now.time_of_day().seconds());
	return date;
}

string convert_timezone(string time, string zoneCode, string originalZoneCode) {
	time_zone_ptr zone(new posix_time_zone(zoneCode));
	time_zone_ptr originalZone(new posix_time_zone(originalZoneCode));
	ptime t(time_from_string(time));
	ptime newTime = t + zone->base_utc_offset() - originalZone->base_utc_offset();
	return to_simple_string(newTime);
}

int compare_date(string time1, string time2) {
	stringstream ss1(time1);
	stringstream ss2(time2);
	string temp;
	getline(ss1, temp, '/');
	int day = stoi(temp);
	getline(ss1, temp, '/');
	int month;
	if(temp[0] >= '0' && temp[0] <= '9') {
		month = stoi(temp);
	}
	else {
		month = month_string_to_int(temp);
	}
	getline(ss1, temp, '\0');
	int year = stoi(temp);
	date d1(year, month, day);
	getline(ss2, temp, '/');
	day = stoi(temp);
	getline(ss2, temp, '/');
	if (temp[0] >= '0' && temp[0] <= '9') {
		month = stoi(temp);
	}
	else {
		month = month_string_to_int(temp);
	}
	getline(ss2, temp, '\0');
	year = stoi(temp);
	date d2(year, month, day);
	if (d1 < d2) {
		return -1;
	}
	else if (d1 > d2) {
		return 1;
	}
	return 0;
}