#include "Filesystem.h"
#include "Chrono.h"
#include "JSON.h"
#include "Locale.h"
#include "URL.h"
#include "StringAlgo.h"
#include "Tuple.h"
int main() {
	cout << get_current_path() << endl;
	cout << get_file_size("C:/Users/dodin/Desktop/BoostDemo/BoostDemo/.vs/BoostDemo/v17/.suo") << endl;
	cout << get_folder_info(get_current_path()) << endl;
	cout << get_folder_tree(get_current_path(), 0) << endl;

	cout << get_current_time() << endl;
	//support 2 formats: 1 / 1 / 2022, 1 / JAN / 2022
	cout << compare_date("1/1/2022", "28/2/2022") << endl;
	cout << convert_timezone("2023-11-28 22:44:00", "GMT", "GMT+7") << endl;

	boost::json::object obj1({
		{"Name", "Hai Do"}, {"Age", 19},
		{"Class", "22CLC02"}, {"Years of study", 12 },
		{"Hobbies", boost::json::array({"Reading", "Coding", "Gaming", "Watching movies"})},
		{"Is handsome", true},
		{"Languages", boost::json::object({ {"C++", "Beginner"}, {"Python", "Beginner"}, {"Javascript", "Intermediate"}})},
		{"Numbers", boost::json::array({1, 2, 3, 4, 5, 6, 7, 8, 9, 10})}
		});
	boost::json::object obj2({
		{"Name", "Hai"},
		{"Age", 19},
		{"Class", "22CLC02"}, {"Years of study", 12 },
		{"Hobbies", boost::json::array({"Reading", "Coding"})},
		{"Is handsome", true},
		{"Languages", boost::json::object({ {"C++", "Beginner"}, {"Python", "Beginner"}, {"Javascript", "Intermediate"}})},
		{"Numbers", boost::json::array({11,12,13,14,15})}
		});
	string json_str = R"({"Name":"Hai Do","Age":19,"Class":"22CLC02","Years of study":12,"Hobbies":["Reading","Coding","Gaming","Watching movies"],"Is handsome":true,"Languages":{"C++":"Beginner","Python":"Beginner","Javascript":"Intermediate"}})";
	JSON json;
	cout << json.stringify(obj1) << endl;
	cout << json.parse(json_str) << endl;
	cout << json.tree_visualize(obj1) << endl;
	cout << json.tree_visualize(json.merge(obj1, obj2)) << endl;
	cout << json.tree_visualize(json.flatten(obj1)) << endl;

	vector <tuple<int, string, int, double, string, bool>> students;
	students.push_back(make_tuple(1, "Hai", 19, 3.5, "22CLC02", true));
	students.push_back(make_tuple(2, "Hai Do", 19, 4, "22CLC02", true));
	students.push_back(make_tuple(3, "Josh", 19, 3.5, "22CLC02", true));
	for (int i = 0; i < students.size(); i++) {
		cout << get<0>(students[i]) << " " << get<1>(students[i]) << " " << get<2>(students[i]) << " " << get<3>(students[i]) << " " << get<4>(students[i]) << " " << get<5>(students[i]) << endl;
	}
	int id, age, is_handsome;
	string name, class_name;
	double gpa;
	tie(id, name, age, gpa, class_name, is_handsome) = make_tuple(4, "Mary", 19, 3.33, "22CLC02", true); // tier is tuple where all elements are of non-const reference types. They are constructed with a call to the tie function template (make_tuple):
	students.push_back(tie(id, name, age, gpa, class_name, is_handsome));
	for (int i = 0; i < students.size(); i++) {
		cout << get<0>(students[i]) << " " << get<1>(students[i]) << " " << get<2>(students[i]) << " " << get<3>(students[i]) << " " << get<4>(students[i]) << " " << get<5>(students[i]) << endl;
	}
	//Compiling tuples can be slow due to the excessive amount of template instantiations. Depending on the compiler and the tuple length, it may be more than 10 times slower to compile a tuple construct, compared to compiling an equivalent explicitly written class
	boost::system::result<url> AU = parse_absolute_uri("https://www.google.com/search?q=boost+tuple&oq=boost+tuple&aqs=chrome..69i57j0i512l9.2313j0j7&sourceid=chrome&ie=UTF-8");
	boost::system::result<url> OF = parse_origin_form("/search?q=boost+tuple&oq=boost+tuple&aqs=chrome..69i57j0i512l9.2313j0j7&sourceid=chrome&ie=UTF-8");
	boost::system::result<url> RF = parse_relative_ref("//www.google.com/search?q=boost+tuple&oq=boost+tuple&aqs=chrome..69i57j0i512l9.2313j0j7&sourceid=chrome&ie=UTF-8");
	boost::system::result<url> UF = parse_uri_reference("https://www.google.com/search?q=boost+tuple&oq=boost+tuple&aqs=chrome..69i57j0i512l9.2313j0j7&sourceid=chrome&ie=UTF-8");
	boost::system::result<url> URI = parse_uri("https://www.google.com/search?q=boost+tuple&oq=boost+tuple&aqs=chrome..69i57j0i512l9.2313j0j7&sourceid=chrome&ie=UTF-8");
	boost::system::result<ipv4_address> ipv4 = parse_ipv4_address("192.168.1.1");
	boost::system::result<ipv6_address> ipv6 = parse_ipv6_address("2001:0db8:85a3:0000:0000:8a2e:0370:7334");
	if (AU) {
		url U2 = AU.value();
		cout << "Absolute URI: " << U2 << endl;
	}
	if (OF) {
		cout << "Original form URI: " << OF.value() << endl;
	}
	if (RF) {
		cout << "Relative ref URI: " << RF.value() << endl;
	}
	if (UF) {
		cout << "URI ref: " << UF.value() << endl;
	}
	if (URI) {
		cout << "URI: " << URI.value() << endl;
	}
	if (ipv4) {
		cout << ipv4.value() << endl;
	}
	else {
		cout << ipv4.error().message() << endl;
	}
	if (ipv6) {
		cout << ipv6.value() << endl;
	}
	else {
		cout << ipv6.error().message() << endl;
	}
	url url1 = format("{}://{}:{}/rfc/{}", "https", "www.ietf.org", 80, "rfc2396.txt");
	cout << "Created from format: " << url1 << endl;

	string str1 = "Text.exe";
	cout << "Is str1 executable?" << endl;
	if (iends_with(str1, ".exe")) { // check if str1 ends with ".exe", like str1.endswith(".exe") in Python
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}
	string str2 = to_upper_copy(str1); // convert str1 to uppercase, like str1.upper() in Python
	cout << "To upper of str1: " << str2 << endl;
	string str3 = "                             Hai Do          ";
	cout << "str3 before trim: " << str3 << "||" << endl;
	cout << "str3 after trim left: " << trim_left_copy(str3) << "||" << endl; // trim_left_copy(str3) is like str3.lstrip() in Python
	cout << "str3 after trim right" << trim_right_copy(str3) << "||" << endl; // trim_right_copy(str3) is like str3.rstrip() in Python
	cout << "str3 after trim: " << trim_copy(str3) << "||" << endl; // trim_copy(str3) is like str3.strip() in Python
	vector<string> tokens;
	string str4 = "{Name: Hai Do, Age: 19, Class: 22CLC02}";
	split(tokens, str4, is_any_of(", "), token_compress_on); // split str4 into tokens, like str4.split(", ") in Python
	for (int i = 0; i < tokens.size(); i++) {
		cout << tokens[i] << endl;
	}
	return 0;
}