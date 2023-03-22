#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

#define RATIO 7.5345

using namespace std;

int main() {
	string line, result;
	while (getline(cin, line)) {
		result.append(line);
		result.append("\n");
	}
	size_t start = 0, hrk;
	do {	
		hrk = result.find("HRK", start);
		start = hrk + 3;
		size_t kraj = 0, poc = 0;
		if (hrk == 0)
			continue;
		if (hrk == string::npos)
			break;
		kraj = result.find_last_not_of(" \t\f\v\n\r", hrk - 1);
		poc = result.find_last_not_of("0123456789.-", kraj);
		if (poc < kraj) {
			string kune_str = result.substr(poc + 1, kraj - poc);
			try {
				float kune = stof(kune_str);
				float euri = kune / RATIO;
				stringstream stream;
				stream << fixed << setprecision(2) << euri;
				string euri_str = stream.str();
				result.replace(hrk, 3, "EUR");
				result.replace(poc + 1, kraj - poc, euri_str);
			} catch (invalid_argument) {}
		} 
	} while (hrk != string::npos);
	cout << result;
}
