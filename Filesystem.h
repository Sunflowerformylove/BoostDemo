#pragma once
#include <boost/filesystem.hpp>
#include <string>
#include <iostream>
#include <cstdint>
using namespace std;
using namespace boost::filesystem;

double format_file_size(uint64_t size, int &sizeType);
uint64_t get_folder_size(string pathname);
string get_size_type(int sizeType);
string get_current_path();
uint64_t get_file_size(string path);
string replace_all(string str, char finder, char replacer);
string replace_all(string str, string finder, string replacer);
string get_file_info(string pathname);
string get_folder_info(string pathname);
string get_folder_tree(string pathname, int indent = 0);
void move_file(string source, string destination);
void rename_file(string source, string destination);