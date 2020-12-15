/*
diy small file handler to make writing and reading from txt files easier.
this is NOT very efficient, and makes use of some "bad" practices.

*/

#include <vector>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "file_handler.h"

//vars:
string filename;
ofstream outfile;
string outName = filename;
vector<string> text;

//NOW I KNOW WHY YA DONT WANNA USE STANDARD NAMESPACE
//constructor:
file_handler::file_handler(string f_name, int NorOl) { // apparently, supply default arguments in header file only
	filename = f_name;
	outName = filename;
	if (NorOl == 0) {
		outName += ".txt"; // save as txt file
	}
}

void file_handler::makefile() {
	outfile.open(outName);

	if (outfile.is_open()) {
		outfile.close();
		cout << "txt file generated. " << endl;
	}
	else {
		cout << "could not create file: " << outName << endl;
	}
}

void file_handler::writefile(string data) {
	int open_state = 0;
	outfile.open(outName, ios::app); // iostream app = append to list of characters.

	if (outfile.is_open()) {
		open_state = 1;
		cout << "file opened!" << endl;
	}
	else {
		open_state = 0;
		cout << "File open error." << endl;
	}
	cout << "writing to a file: " << data << endl;

	outfile << data << endl;

	outfile.close();
}

void file_handler::readfile() { // I don't think this is workins as intended.
	string infilen = outName;
	string output;
	ifstream infile;
	string line;
	infile.open(outName);
	if (infile.is_open()) {
		cout << "file opened: " << outName << endl;

		while (!infile.eof()) {
			getline(infile, line);
			cout << line << endl;
			text.push_back(line);
		}
	}
	else {
		cout << "file open error: " << outName << endl;
	}
}

vector<string> file_handler::getvals() {
	return text;
}
