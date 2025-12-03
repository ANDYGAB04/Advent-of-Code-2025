#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
using namespace std;
struct Number {
	int digit;
	int poz;
};
void solve1() {
	string num;
	long long sum = 0;
	while (cin >> num) {
		string number = "";
		if (num == "0") {
			break;
		}
		for (auto i = 9; i >= 1; i--) {
			auto it = num.find(to_string(i));
			if (it != string::npos && it < num.size() - 1) {
				number += num[it];
				num = num.substr(it+1, num.size());
				break;
			}
		}
		for (auto i = 9; i >= 1; i--) {
			auto it = num.find(to_string(i));
			if (it != string::npos) {
				number += num[it];
				break;
			}
		}
		sum += stoll(number);

	}
	cout << sum << endl;
}
void solve2() {
	string num;
	long long sum = 0;
	while (cin >> num) {
		if (num == "0") {
			break;
		}
		
		int toSelect = 12;
		int toRemove = num.size() - toSelect;
		string result = "";
		
		for (int i = 0; i < num.size(); i++) {
			while (!result.empty() && toRemove > 0 && result.back() < num[i]) {
				result.pop_back();
				toRemove--;
			}
			result += num[i];
		}
		
		result = result.substr(0, toSelect);
		
		sum += stoll(result);
	}
	cout << sum << endl;

}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;

}