#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
	priority_queue<int, vector<int>, greater<int>> pq;
	int x;
	while (cin >> x)
		if (x >= 0 && x <= 1000)
			pq.push(x);
	if (pq.top() != 0) 
		cout << "[0," << pq.top() - 1 << "]" << endl;
	while (!pq.empty()) {
		int top = pq.top();
		cout << "[" << top + 1 << "," << top - 1 << "]" << endl;
		pq.pop();
	}
}
