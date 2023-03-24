#include <iostream>
#include <vector>

#define UPPER 1000

using namespace std;

void print_interval(int left, int right) {
	cout << "[" << left << "," << right << "]" << endl;
}

int main() {
	vector<int> niz;
	int unos;
	while (cin >> unos)
		if (unos >= 0 && unos <= UPPER) {
			auto iter = niz.begin();

			// Ubacujemo na mjesto tako da niz ostane sortiran.
			while (!niz.empty() && *iter > unos)
				++iter;
			niz.insert(iter, unos);
		}
	int current = 0;

	// Obratni iterator nam zapravo daje uzlazno sortirane 
	// elemente niza, dakle pracenjem varijable `current` i
	// usporedbom s elementima niza mozemo odrediti intervale.
	for (auto it = niz.rbegin(); it != niz.rend(); ++it) {
		if (*it > current)
			print_interval(current, *it - 1);	
		current = *it + 1;
	}
	if (current <= UPPER)
		print_interval(current, UPPER);
}
