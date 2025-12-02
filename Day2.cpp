#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
using namespace std;
struct Id {
	long long left;
	long long right;
};
void solve() {
	string Ids;
	cin >> Ids;
	vector <Id> ids;
	while (!Ids.empty()) {
		auto it = Ids.find(',');
		if (it != string::npos) {
			string aux = Ids.substr(0, it);
			Ids.erase(0, it + 1);
			Id id;
			id.left = stoll(aux.substr(0, aux.find('-')));
			id.right = stoll(aux.substr(aux.find('-') + 1, aux.size() - 1));
			ids.push_back(id);
		}
		else {
			string aux = Ids.substr(0, Ids.size());
			Ids.erase(0, Ids.size());
			Id id;
			id.left = stoll(aux.substr(0, aux.find('-')));
			id.right = stoll(aux.substr(aux.find('-') + 1, aux.size() - 1));
			ids.push_back(id);
		}
	}
	long long sumofids = 0;
	for (auto id : ids) {
		for (long long i = id.left; i <= id.right; i++) {
			string testid = to_string(i);
			if (testid.size() % 2 == 0) {
				if (testid.substr(0, testid.size() / 2) == testid.substr(testid.size() / 2, testid.size())) {
					sumofids += i;
				}
				else {
					int n = (int)testid.length();
					vector<int> pi(n);
					for (int idx = 1; idx < n; idx++) {
						int j = pi[idx - 1];
						while (j > 0 && testid[idx] != testid[j])
							j = pi[j - 1];
						if (testid[idx] == testid[j])
							j++;
						pi[idx] = j;
					}
					
					int patternLength = n - pi[n - 1];
					if (pi[n - 1] > 0 && n % patternLength == 0) {
						sumofids += i;
					}
				}
			}
			else {
				int n = (int)testid.length();
				vector<int> pi(n);
		
				for (int idx = 1; idx < n; idx++) {
					int j = pi[idx - 1];
					while (j > 0 && testid[idx] != testid[j])
						j = pi[j - 1];
					if (testid[idx] == testid[j])
						j++;
					pi[idx] = j;
				}
				
				int patternLength = n - pi[n - 1];
				if (pi[n - 1] > 0 && n % patternLength == 0) {
					sumofids += i;
				}
			}
		}
	}
	cout << sumofids;

}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
	return 0;

}