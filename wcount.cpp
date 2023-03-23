#include <iostream>
#include <string>
#include <deque>
#include <map>

using namespace std;

void print_word(string &word, map<string, int> &freq) {
	cout << word << " " << freq.find(word)->second << endl;
}

int main() {
	deque<string> words;
	map<string, int> occurences;

	string unos;
	while (cin >> unos) {
		words.push_front(unos);
		occurences.insert({unos, 0});
	}
	for (string &word : words)
		occurences.find(word)->second++;
	for (string &word : words)
		print_word(word, occurences);
}
