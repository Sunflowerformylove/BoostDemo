#include "JSON.h"
using namespace std;

void format_string(string& str) {
	// remove all spaces
	str.erase(remove(str.begin(), str.end(), ' '), str.end());
	// remove all tabs
	str.erase(remove(str.begin(), str.end(), '\t'), str.end());
	// remove all newlines
	str.erase(remove(str.begin(), str.end(), '\n'), str.end());
}

void tokenize(string str, vector<vector<string>>& tokens) {
	//in object, it can be simplified as pairs of key-value,
	//so we can tokenize the string by splitting it into pairs of key-value
	//then, we can tokenize each pair into key and value string, separated by ":",
	//which means we need a 2D vector to store the tokens
	stringstream ss(str);
	string pair;
	while (getline(ss, pair, ',')) {
		vector<string> token;
		stringstream ss2(pair);
		string key_value;
		while (getline(ss2, key_value, ':')) {
			token.push_back(key_value);
		}
		tokens.push_back(token);
	}
}

string JSON::check_type(boost::json::value val)
{
	if (val.is_array()) {
		return "array";
	}
	else if (val.is_bool()) {
		return "bool";
	}
	else if (val.is_double()) {
		return "double";
	}
	else if (val.is_int64()) {
		return "int64";
	}
	else if (val.is_null()) {
		return "null";
	}
	else if (val.is_object()) {
		return "object";
	}
	else if (val.is_string()) {
		return "string";
	}
	else if (val.is_uint64()) {
		return "uint64";
	}
	return "null";
}

string JSON::stringify_val(boost::json::value val)
{
	if (this->check_type(val) == "string") {
		return val.as_string().c_str();
	}
	else if (this->check_type(val) == "array") {
		string result = "[";
		for (int i = 0; i < val.as_array().size(); i++) {
			result += this->stringify_val(val.as_array()[i]);
			if (i < val.as_array().size() - 1) {
				result += ", ";
			}
			if (i == val.as_array().size() - 1) {
				result += "]";
			}
		}
		return result;
	}
	else if (this->check_type(val) == "object") {
		return this->stringify(val.as_object());
	}
	else if (this->check_type(val) == "bool") {
		return val.as_bool() ? "true" : "false";
	}
	else if (this->check_type(val) == "null") {
		return "null";
	}
	else if (this->check_type(val) == "int64") {
		return to_string(val.as_int64());
	}
	else if (this->check_type(val) == "uint64") {
		return to_string(val.as_uint64());
	}
	else if (this->check_type(val) == "double") {
		return to_string(val.as_double());
	}
	return string();
}

string JSON::stringify(boost::json::object JSON_obj, bool is_recursive) {
	// JSON in boost provide object, which is a map<string, value> like object in JS
	// also provide array, which is a vector<value> like array in JS
	// value is a variant, which can be string, int64_t, double, bool, object, array, null, the type of value will be assign at runtime
	string result = "{\n";
	for (const auto& prop : JSON_obj) {
		result += "\t"; // tab characters
		if (is_recursive) {
			result += "\"";
			result += prop.key();
			result += "\""; // escape character
		}
		else {
			result += prop.key();
		}
		if (prop.value().is_string()) {
			result += ":\""; // escape character
			result += prop.value().as_string().c_str();
			result += "\""; // escape character
			result += ",\n";
		}
		else if (prop.value().is_array()) {
			result += ": \"[";
			for (int i = 0; i < prop.value().as_array().size(); i++) {
				result += stringify_val(prop.value().as_array()[i]);
				if (i < prop.value().as_array().size() - 1) {
					result += ", ";
				}
				if (i == prop.value().as_array().size() - 1) {
					result += "]\"";
					result += ",\n";
				}
			}
		}
		else if (prop.value().is_object()) {
			result += ": ";
			result += stringify(prop.value().as_object(), true);
			result += ",\n";
		}
		else if (prop.value().is_bool()) {
			result += ": ";
			result += prop.value().as_bool() ? "\"true\"" : "\"false\"";
			result += ",\n";
		}
		else if (prop.value().is_null()) {
			result += ": null";
			result += ",\n";
		}
		else {
			result += ": \"";
			if (prop.value().is_int64()) {
				result += to_string(prop.value().as_int64());
			}
			else if (prop.value().is_double()) {
				result += to_string(prop.value().as_double());
			}
			else if (prop.value().is_uint64()) {
				result += to_string(prop.value().as_uint64());
			}
			result += "\",\n";
		}
	}
	return result + "\n}";
}

boost::json::object JSON::parse(string JSON_str) {
	boost::json::value val = boost::json::parse(JSON_str);
	boost::json::object result;
	for (const auto& prop : val.as_object()) {
		result[prop.key()] = prop.value();
	}
	return result;
}

string JSON::tree_visualize(boost::json::object JSON_obj, int indent) {
	string result = "{\n";
	for (const auto& prop : JSON_obj) {
		for (int i = 0; i < indent; i++) {
			result += "\t";
		}
		result += prop.key();
		result += ": ";
		if (prop.value().is_string()) {
			result += "\"";
			result += string(prop.value().as_string().c_str());
			result += "\"";
			result += ",\n";
		}
		else if (prop.value().is_array()) {
			result += "[";
			for (int i = 0; i < prop.value().as_array().size(); i++) {
				result += this->stringify_val(prop.value().as_array()[i]);
				if (i < prop.value().as_array().size() - 1) {
					result += ", ";
				}
				if (i == prop.value().as_array().size() - 1) {
					result += "]";
					result += ",\n";
				}
			}
		}
		else if (prop.value().is_object()) {
			result += tree_visualize(prop.value().as_object(), indent + 2);
			result += ",\n";
		}
		else if (prop.value().is_bool()) {
			result += prop.value().as_bool() ? "true" : "false";
			result += ",\n";
		}
		else if (prop.value().is_null()) {
			result += "NULL";
			result += ",\n";
		}
		else {
			if (prop.value().is_int64()) {
				result += to_string(prop.value().as_int64());
			}
			else if (prop.value().is_double()) {
				result += to_string(prop.value().as_double());
			}
			else if (prop.value().is_uint64()) {
				result += to_string(prop.value().as_uint64());
			}
			result += ",\n";
		}
	}
	result + "\n";
	for (int i = 0; i < indent - 1; i++) {
		result += "\t";
	}
	result += "}";
	return result;
}

boost::json::object JSON::merge(boost::json::object JSON1, boost::json::object JSON2) {
	boost::json::object result;
	for (const auto& prop : JSON1) {
		result[prop.key()] = prop.value();
	}
	for (const auto& prop : JSON2) {
		if (prop.value().is_array()) {
			for (const auto& val : prop.value().as_array()) {
				result[prop.key()].as_array().push_back(val);
			}
		}
		else if (prop.value().is_object()) {
			result[prop.key()] = this->merge(result[prop.key()].as_object(), prop.value().as_object());
		}
		else {
			result[prop.key()] = prop.value();
		}
	}
	return result;
}

boost::json::object JSON::flatten(boost::json::object JSON) {
	boost::json::object result;
	for (const auto& prop : JSON) {
		if (prop.value().is_object()) {
			boost::json::object temp = this->flatten(prop.value().as_object());
			for (const auto& prop2 : temp) {
				string name = prop.key();
				name += ".";
				name += prop2.key();
				result[name] = prop2.value();
			}
		}
		else {
			result[prop.key()] = prop.value();
		}
	}
	return result;
}