#pragma once
#include <boost/json.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cstring>
using namespace std;

class JSON {
public:
	string check_type(boost::json::value val);
	string stringify_val(boost::json::value val);
	string stringify(boost::json::object JSON_obj, bool is_recursive = false);
	boost::json::object parse(string JSON_str);
	string tree_visualize(boost::json::object JSON_obj, int indent = 0);
	boost::json::object merge(boost::json::object JSON1, boost::json::object JSON2);
	boost::json::object flatten(boost::json::object JSON);
};