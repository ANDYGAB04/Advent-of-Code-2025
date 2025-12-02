#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;
void solve() {
	string rotation;
	int nrRotation = 0;
	int start = 50;
	while (cin >> rotation) {
		if (rotation == "0") {
			break;
		}
		if (rotation.size() == 2) {
			if (rotation[0] == 'L') {
				start -= stoi(rotation.substr(1));
			}
			else
				start += stoi(rotation.substr(1));

		}
		else if (rotation.size() == 3) {
			if (rotation[0] == 'L') {
				start -= stoi(rotation.substr(1, 2));
			}
			else
				start += stoi(rotation.substr(1, 2));
		}
		else {
			if (rotation[0] == 'L') {
				start -= stoi(rotation.substr(1, 3));
			}
			else
				start += stoi(rotation.substr(1, 3));
		}

		while (start > 99) {
			start -= 100;
		}
		while (start < 0) {
			start += 100;
		}

		if (start == 0) {
			nrRotation++;
		}
	}
	std::cout << nrRotation;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;

}