#ifndef FILE_HANDLER_H_
#define FILE_HANDLER_H_

#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;
//use headers to create function proto.
//just follow this (if this works)

class file_handler
{
private:
	string filename;
	ofstream outfile;
	string outName = filename;
	vector<string> text;

public:
	file_handler(string f_name, int NorOl = 0);
	void makefile();
	void writefile(string data);
	void readfile();
	vector<string> getvals();
};

#endif FILE_HANDLER_H_