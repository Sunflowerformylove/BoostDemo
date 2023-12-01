#pragma once
#include <string>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <boost/chrono.hpp>
#include <boost/date_time.hpp>
using namespace std;
using namespace boost::chrono;
using namespace boost::gregorian;
using namespace boost::posix_time;
using namespace boost::local_time;

const string MONTHS[12] = { "JAN", "FEB", "MAR", "APR", "MAY", "JUN", "JUL", "AUG", "SEP", "OCT", "NOV", "DEC" };

int month_string_to_int(string month);
string get_current_time();
string convert_timezone(string time, string zoneCode, string originalZoneCode);
int compare_date(string time1, string time2);