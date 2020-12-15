#ifndef ALGS_H_
#define ALGS_H_

using namespace std;

class algs
{
public:
	string cscipher(int key, string text);

	string beaufort(string text, string key, string charset);

	string XOR_base(string key, string phrase);

	char charOnlyXOR_base(char key_frag, char lettr);

	string keymake(int M_iter, int Mkey); // i wanna use a struct for this, but nah
};



#endif ALGS_H_