#include <string>
#include <iostream>
#include <vector>

#include "encrypt.h"
#include "algs.h"

// variables
string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int key_length = 0;
int key1 = 0; // gets len
int key2 = 0;
int key3 = 0;
int k1_loc = 0;
int k2_loc = 0;
int k3_loc = 0;
string temp = "";
string pass1, pass2;

// functions
void reset() {
	key_length = 0;
	key1 = 0;
	key2 = 0;
	key3 = 0;
	k1_loc = 0;
	k2_loc = 0;
	k3_loc = 0;
	temp = "";
	pass1 = "";
	pass2 = "";
	cout << "values reset." << endl;
}

void encrypt::show_values() {
	cout << "key1_len: " << key1 << endl;
	cout << "key2_len: " << key2 << endl;
	cout << "key3_len: " << key3 << endl;

	cout << "key1_loc: " << k1_loc << endl;
	cout << "key2_loc: " << k2_loc << endl;
	cout << "key3_loc: " << k3_loc << endl;
}

string encrypt::enc(string key, string raw_text) {
	reset(); // idk if deconstructing would be an alternative to this
	string output;
	//get key separation

	//get key sep + ;loc:
	for (int i = 0; i < key.length(); i++) { // get k1 len
		if (key[i] != '-') {
			key1++;
		}
		else if (key[i] == '-') {
			key_length = i;
			k2_loc = (i + 1);
			//cout << key1 << endl;
			break;
		}
	}
	key_length = key_length + 1;
	for (int j = key_length; j < key.length(); j++) { // get k2 len
		if (key[j] != '-') {
			key2++;
		}
		else if (key[j] == '-') {
			key_length = (j + 1);
			k3_loc = (j + 1);
			break;
		}
	}
	for (int k = key_length; k < key.length(); k++) {
		if (key[k] != '-') {
			key3++;
		}
		else if (key[k] == '-') {
			break;
		}
	}
	// get rand char amt
	string temp = "";
	for (int o = 0; o <= 1; o++) {
		temp += key[o];
	}

	// get beau phrase
	string Pphrase;
	for (int m = k2_loc; m <= (key2 + 2); m++) {
		Pphrase += key[m];
	}

	// get ciph key
	string ckey = "";
	for (int n = (k3_loc); n < (key.length() - 1); n++) {
		ckey += key[n];
	}

	//start encryption
	int n_char = stoi(temp);
	for (int l = 0; l < n_char; l++) {
		int choice = (rand() % 25);
		output += alphabet[choice];
	}

	// get alg instances:

	algs inst;

	// passphrase is known, pass through function, store to temp var
	string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string first_pass = inst.beaufort(raw_text, Pphrase, charset);

	// pass through ciph:
	int ciph_key = stoi(ckey); // pass ckey string to stoi, get number
	string second_pass = inst.cscipher(ciph_key, first_pass); // encrypt

	// append to output string:
	output += second_pass;
	return output;
}

string encrypt::decr(string key, string raw_text) {
	reset();
	string output;

	for (int i = 0; i < key.length(); i++) { // get k1 len
		if (key[i] != '-') {
			key1++;
		}
		else if (key[i] == '-') {
			key_length = i;
			k2_loc = (i + 1);
			//cout << key1 << endl;
			break;
		}
	}
	key_length = key_length + 1;
	for (int j = key_length; j < key.length(); j++) { // get k2 len
		if (key[j] != '-') {
			key2++;
		}
		else if (key[j] == '-') {
			key_length = (j + 1);
			k3_loc = (j + 1);
			break;
		}
	}
	for (int k = key_length; k < key.length(); k++) {
		if (key[k] != '-') {
			key3++;
		}
		else if (key[k] == '-') {
			break;
		}
	}

	// get keys

	for (int o = 0; o <= 2; o++) {
		temp += key[o];
	}

	int n_char = stoi(temp);

	//use first key to remove chars from string
	//cout << "char_n: " << n_char << endl;
	for (int l = n_char; l < raw_text.length(); l++) { // use this to remove chars
		output += raw_text[l];
	}

	// get beau phrase;
	string Pphrase;
	for (int m = k2_loc; m <= (key2 + 2); m++) {
		Pphrase += key[m];
	}

	// get ciph key
	string ckey = "";
	for (int n = (k3_loc); n < (key.length() - 1); n++) {
		ckey += key[n];
	}
	// get alg instance:
	algs decrypt;
	//decode everything, pray it works
	int caes_key = stoi(ckey);
	pass1 = decrypt.beaufort(output, Pphrase, alphabet);

	pass2 = decrypt.cscipher(caes_key, pass1);
	output = pass2;

	//return
	return output;
}

string encrypt::XOR_alg(string phrase, string key) {
	string output;
	algs algss;
	vector<char> phrase_array;

	//get phrase and store as char vector
	for (int i = 0; i < phrase.size(); i++) {
		phrase_array.push_back(phrase[i]);
	}
	// start using XOR, add to output string.
	int j = 0;
	for (int i = 0; i < phrase.size(); i++) {
		if (j < key.size()) {
			output += (phrase_array[i] ^ key[j]);
			j++;
		}
		else if (j == key.size()) {
			j = 0;
			output += (phrase_array[i] ^ key[j]);
		}
	}
	return output;
}