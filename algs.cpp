#include <string>

#include "algs.h"

string algs::cscipher(int key, string text) {
	string result = "";

	// traverse text
	for (int i = 0; i < text.length(); i++)
	{
		// apply transformation to each character
		// Encrypt Uppercase letters
		if (isupper(text[i]))
			result += char(int(text[i] + key - 65) % 26 + 65);

		// Encrypt Lowercase letters
		else
			result += char(int(text[i] + key - 97) % 26 + 97);
	}

	// Return the resulting string
	return result;
}

string beaufort(string text, string key, string charset) {
	string cipher;
	string alphabet = charset;
	for (int i = 0; i < text.size(); i++) {
		char c0 = text[i];
		char c1 = key[i % key.size()];
		int start = 0;
		for (int j = 0; j < 26; j++) {
			if (alphabet[j] == toupper(c0)) {
				start = j;
				break;
			}
		}
		int offset = 0;
		for (int j = start; j < start + 26; j++) {
			int letter = j % 26;
			if (alphabet[letter] == toupper(c1)) {
				break;
			}
			offset++;
		}
		cipher += alphabet[offset];
	}
	return cipher;
}

string algs::XOR_base(string key, string phrase) {
	string output = phrase;

	for (int i = 0; i < phrase.size(); i++) {
		int j = 0;
		output[i] = phrase[i] ^ key[j];
		if (j < key.size()) {
			j++;
		}
		else {
			j = 0;
		}
	}

	return output;
}

char algs::charOnlyXOR_base(char key_frag, char lettr) {
	char output;

	output = lettr ^ key_frag;

	return output;
}

string algs::keymake(int M_iter, int Mkey) { // generates the key for encryption, does not account for the other type. might make this one user supplied.
	string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string output = "";
	string k1 = "";
	int k2;
	int keylength = rand() % Mkey;
	keylength = keylength = 10;
	int times = (rand() + 1) % M_iter;
	output += to_string(times + 1);
	output += '-';

	for (int i = 0; i <= keylength; i++) {
		int temp = rand() % 25;
		k1 += alphabet[temp];
	}
	output += k1;
	output += '-';

	int t = (rand() % 25);
	k2 = t + 1;
	output += to_string(k2);
	output += '-';
	return output;
}