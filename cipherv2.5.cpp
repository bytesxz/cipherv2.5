#include <iostream>
#include <time.h>
#include "file_handler.h"
#include "algs.h"
#include "encrypt.h"

using namespace std;

class testers {
private:

public:

	string run_test(string phrase, int x = 0) {
		algs alg;
		string yes = alg.keymake(100, 20);

		encrypt st;
		string nooo = st.enc(yes, "jiajia");

		if (x == 0) {
			;
		}
		else if (x == 1) {
			st.show_values();
		}

		cout << "key: " << yes << endl;
		cout << "encrypted: " << nooo << endl;

		string asdf = st.decr(yes, nooo);
		cout << "decrypted: " << asdf << endl;

		return asdf;
	}

	void test_consistency(int amt, string phrase) {
		for (int i = 0; i < amt; i++) {
			string decr = run_test(phrase);
		}
	}

	void testFileHandling() {
		file_handler hopeitworks("testtesttest", 0);
		hopeitworks.writefile("1");
		hopeitworks.writefile("2");
		hopeitworks.writefile("3");
		hopeitworks.writefile("4");

		hopeitworks.readfile();

		file_handler testopen("research", 0);
		testopen.readfile();
	}

	void encryptTxt_test(string inputfile, string outputfile, string key) {
		// variables
		vector<string> input_txt;

		// get instances for encryption
		file_handler getfile(inputfile);
		getfile.readfile();
		input_txt = getfile.getvals();

		// make a file that will be outputted to
		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//we now have the values, encrypt
		encrypt file;
		string temp = "";
		int yes = input_txt.size();
		for (int i = 0; i < input_txt.size(); i++) {
			temp = file.enc(key, input_txt[i]);
			encryptedfile.writefile(temp);
			if (i > 0) {
				file.show_values();
				cout << "progress: " << i << "/" << temp << endl;
			}
		}
	}

	void decryptTxt_test(string inputfile, string outputfile, string key) {
		// variables
		vector<string> input_txt;

		// get instances for encryption
		file_handler fileget(inputfile);
		fileget.readfile();
		input_txt = fileget.getvals();

		// make a file that will be outputted to
		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//we now have the values, encrypt
		encrypt file;
		string temp = "";
		for (int i = 0; i < input_txt.size(); i++) {
			temp = file.decr(key, input_txt[i]);
			encryptedfile.writefile(temp);
			file.show_values();
			cout << "line: " << temp << endl;
		}
	}

	void test_all() {
		algs getkey;
		string key = getkey.keymake(100, 20);
		string key2 = "thisisakeyyes";
		cout << "key: " << endl;
		testers test;
		test.encryptTxt_test("test_encryption", "test_encrypted", key);

		test.decryptTxt_test("test_encrypted", "test_decrypted", key);
	}

	void with_XOR(string XOR_k, string inputfile, string outputfile) {
		algs getkey;
		string key = getkey.keymake(100, 20);
		string key2 = XOR_k;
		cout << "K1: " << key << endl;
		cout << "K2: " << key2 << endl;

		// variables
		vector<string> input_txt;

		// get instances for encryption
		file_handler getfile(inputfile);
		getfile.readfile();
		input_txt = getfile.getvals();

		// make a file that will be outputted to
		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//we now have the values, encrypt
		encrypt file;
		string temp = "";
		for (int i = 0; i < input_txt.size(); i++) {
			temp = file.XOR_alg(key, input_txt[i]);
			encryptedfile.writefile(temp);
			//cout << "line: " << temp << endl;
		}
	}

	void restructure_file(string input_file) {
		cout << "start file restructure." << endl;

		vector<string> input;
		vector<string> output;
		file_handler getfile(input_file);
		getfile.readfile();
		input = getfile.getvals();
		// turn all lowercase letters to uppercase;
		vector<string> temp;
		for (int i = 0; i < input.size(); i++) {
			string temp_string = input[i];
			string converted_string;
			for (int j = 0; j < temp_string.size(); j++) {
				converted_string += toupper(temp_string[j]);
			}
			output.push_back(converted_string);
		}
		string outputfile = input_file + "_restruc";

		file_handler encryptedfile(outputfile);
		encryptedfile.makefile();

		//rewrite file
		for (int i = 0; i < input.size(); i++) {
			encryptedfile.writefile(output[i]);
		}
		cout << "done." << endl;
	}

	void make_testfile(int line_amt, string phrase, int use_Default = 0) {
		//make file handling instance
		const string filename = "testfile";
		string default_phrase = "STARTAAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZEND";
		if (use_Default == 0) {
			;
		}
		else {
			phrase = default_phrase;
		}

		file_handler make_file(filename);
		make_file.makefile();
		file_handler writeto(filename);

		for (int i = 0; i < line_amt; i++) {
			writeto.writefile(phrase);
		}
	}

	int compare_Files(string file_1, string file_2) {
		char cont;
		vector<string> file1;
		vector<string> file2;
		vector<int> state;
		bool is_same = true;


		//make file handler instances and place in its corresponding vectors:
		file_handler first(file_1);
		file_handler second(file_2);

		first.readfile();
		file1 = first.getvals();

		second.readfile();
		file2 = second.getvals();

		if (file1.size() == file2.size()) {
			is_same = true;
		}
		else if (file1.size() != file2.size()) {
			cout << "files are not the same size." << endl;
			is_same = false;
		}

		// make for loop if files are the same len.
		if (is_same == false) {
			cout << "continue with comparison? > " << endl;

		}
		else if (is_same == true) {
			for (int i = 0; i < file1.size(); i++) {
				if (file1[i] == file2[i]) {
					state.push_back(1);
				}
				else {
					state.push_back(0);
				}
			}
		}

		int error_amount = 0;
		for (int i = 0; i < state.size(); i++) {
			if (state[i] == 0) {
				error_amount++;
			}
			else {
				;
			}
		}
		cout << "amount of errors: " << error_amount << endl;
		return error_amount;
	}
};

class build { // abstractttttttt
private:

public:
	void main_testFunc(int amt, int open_files = 0) { // im too lazy to add arguments :))
		testers instance1;
		algs make;
		for (int i = 0; i < amt; i++) {
			string key = make.keymake(20, 100);
			instance1.restructure_file("test_encryption"); // this can be faster by testers::restructure file be a private thing.
			instance1.encryptTxt_test("test_encryption_restruc", "encrypted", key);
			instance1.decryptTxt_test("encrypted", "decryptedtxt", key);
		}
	}

	void testXOR(string phrase, string key, int debug_state = 0) {
		string phrase_in = phrase;
		string phrase_out;
		int is_correct;

		encrypt xorinst;
		phrase_out = xorinst.XOR_alg(phrase_in, key);
		string decrypted = xorinst.XOR_alg(phrase_out, key);

		if (debug_state == 0) {
			;
		}
		else if (debug_state == 1) {
			cout << "p_in: " << phrase_in << endl;
			cout << "key: " << phrase_in << endl;
			cout << "p_out: " << phrase_out << endl;
			cout << "decrypted: " << decrypted << endl;
			if (phrase_in == decrypted) {
				is_correct = 1;
				cout << "state: " << "::::PASS::::" << endl;
			}
			else if (phrase_in != decrypted) {
				is_correct = 0;
				cout << "state: " << "::::FAIL::::" << endl;
			}
		}
	}
};

int main() {
	srand(time(0));



	return 0;
}
