#ifndef ENCRYPT_H_
#define ENCRYPT_H_

#include <string>

using namespace std;
class encrypt
{
private:
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


public:
	void show_values();

	string enc(string key, string raw_text);

	string decr(string key, string raw_text);

	string XOR_alg(string phrase, string key);
};

#endif ENCRYPT_H_