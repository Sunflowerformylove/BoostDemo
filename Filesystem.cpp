#include "Filesystem.h"

double format_file_size(uint64_t size, int& sizeType) { //format file size in bytes to a more readable format
	double newSize = double(size);
	sizeType = 0;
	while (newSize >= 1024) {
		newSize /= 1024;
		sizeType++;
	}
	return newSize;
}

uint64_t get_folder_size(string pathname) { //get the size of a folder
	if (!exists(pathname)) {
		return -1;
	}
	else if (!is_directory(pathname)) {
		return -1;
	}
	path p(pathname);
	uint64_t size = 0;
	directory_iterator it(p);
	for (const auto& entry : it) {
		if (is_regular_file(entry.path())) {
			size += file_size(entry.path());
		}
		else if (is_directory(entry.path())) {
			size += get_folder_size(entry.path().string());
		}
	}
	return size;
}

string get_size_type(int sizeType) { //get the size type of a file size
	switch (sizeType) {
	case 0:
		return "bytes";
	case 1:
		return "KB";
	case 2:
		return "MB";
	case 3:
		return "GB";
	case 4:
		return "TB";
	case 5:
		return "PB";
	case 6:
		return "EB";
	case 7:
		return "ZB";
	case 8:
		return "YB";
	default:
		return "bytes";
	}
	return "";
}

string get_current_path() {
	return current_path().string();
}

uint64_t get_file_size(string path) {
	if (!exists(path)) {
		return -1;
	}
	else if (!is_regular_file(path)) {
		return -1;
	}
	return file_size(path); //get file size in bytes
}

string replace_all(string str, char finder, char replacer) { //replace all occurences of a character in a string
	size_t pos = str.find(finder);
	while (pos != string::npos) {
		str[pos] = replacer;
		pos = str.find(finder);
	}
	return str;
}

string replace_all(string str, string finder, string replacer) {
	//replace all occurences of a substring in a string
	size_t pos = str.find(finder);
	while (pos != string::npos) {
		str.replace(pos, finder.length(), replacer);
		pos = str.find(finder, pos + replacer.length());
	}
	return str;
}

string get_file_info(string pathname) {
	if (!exists(pathname)) {
		return "File does not exist.";
	}
	else if (!is_regular_file(pathname)) {
		return "Path is not a file.";
	}
	string info = "";
	info += "File size: " + to_string(file_size(pathname));
	info += " bytes\n";
	info += "Last modified: " + to_string(last_write_time(pathname)) + "\n";
	info += "Permissions: " + to_string(status(pathname).permissions()) + "\n";
	info += "Type: " + to_string(status(pathname).type()) + "\n";
	info += "Absolute path: " + absolute(pathname).string() + "\n";
	info += "Canonical path: " + canonical(pathname).string() + "\n";
	info += "Current path: " + current_path().string() + "\n";
	info += "Relative path: " + relative(pathname).string() + "\n";
	return info;
}

string get_folder_info(string pathname) {
	int sizeType = 0;
	if (!exists(pathname)) {
		return "Folder does not exist.";
	}
	else if (!is_directory(pathname)) {
		return "Path is not a folder.";
	}
	path p(pathname);
	cout << pathname << endl;
	string info = "";
	info += "Last modified: " + to_string(last_write_time(pathname)) + "\n";
	info += "Permissions: " + to_string(status(pathname).permissions()) + "\n";
	info += "Type: " + to_string(status(pathname).type()) + "\n";
	info += "Absolute path: " + absolute(pathname).string() + "\n";
	info += "Canonical path: " + canonical(pathname).string() + "\n";
	info += "Current path: " + current_path().string() + "\n";
	info += "Relative path: " + relative(pathname).string() + "\n";
	info += "Number of files: " + to_string(distance(directory_iterator(pathname), directory_iterator())) + "\n";
	info += "Number of subdirectories: " + to_string(distance(recursive_directory_iterator(pathname), recursive_directory_iterator())) + "\n";
	info += "Number of hard links: " + to_string(hard_link_count(pathname)) + "\n";
	info += "Size: " + to_string(format_file_size(get_folder_size(pathname), sizeType));
	info += " " + get_size_type(sizeType) + "\n";
	return info;
}

string get_folder_tree(string pathname, int indent) {
	if (!exists(pathname)) {
		return "Folder does not exist.";
	}
	string tree = "";
	for (int i = 0; i < indent; i++) {
		tree += " ";
	}
	tree += path(pathname).filename().string() + "\n";
	if (is_directory(pathname)) {
		path p(pathname);
		directory_iterator it(p);
		for (const auto& entry : it) {
			tree += get_folder_tree(entry.path().string(), indent + 2);
		}
	}
	return tree;
}

void move_file(string source, string destination) {
	if (!exists(source)) {
		cout << "Source file does not exist." << endl;
		return;
	}
	else if (!is_regular_file(source)) {
		cout << "Source path is not a file." << endl;
		return;
	}
	else if (!exists(destination)) {
		cout << "Destination does not exist." << endl;
		return;
	}
	copy_file(source, destination);
	remove(source);
}

void rename_file(string source, string destination) {
	rename(source, destination);
}