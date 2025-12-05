#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
#include <set>
using namespace std;
struct Id {
	long long left;
	long long right;
};
void solve1() {
	string ingridientId;
	vector<Id> ingridientIds;
	while (getline(cin,ingridientId)) {
		if (ingridientId == "") {
			break;
		}
		Id id;
		id.left= stoll(ingridientId.substr(0, ingridientId.find('-')));
		id.right=stoll(ingridientId.substr(ingridientId.find('-') + 1, ingridientId.size() - 1));
		ingridientIds.push_back(id);

	}
	string id;
	int fresh = 0;
	while (getline(cin, id)) {
		if (id == "") {
			break;
		}
		for (auto ids : ingridientIds) {
			if (ids.left <= stoll(id) && stoll(id) <= ids.right) {
				fresh++;
				break;
			}
		}
	}
	cout << fresh;
}
void solve2() {
	string ingridientId;
	vector<Id> ingridientIds;
	while (getline(cin, ingridientId)) {
		if (ingridientId == "") {
			break;
		}
		Id id;
		id.left = stoll(ingridientId.substr(0, ingridientId.find('-')));
		id.right = stoll(ingridientId.substr(ingridientId.find('-') + 1, ingridientId.size() - 1));
		ingridientIds.push_back(id);

	}
	sort(ingridientIds.begin(), ingridientIds.end(), [](Id a,Id b) {
		return a.left < b.left;
		});

	vector<Id> merged;
	merged.push_back(ingridientIds[0]);
	
	for (auto i = 1; i < ingridientIds.size(); i++) {
		if (merged.back().right >= ingridientIds[i].left) {
			merged.back().right = max(merged.back().right, ingridientIds[i].right);
		} else {
			merged.push_back(ingridientIds[i]);
		}
	}
	long long fresh = 0;
	for (auto ids : merged) {
		fresh += ids.right - ids.left + 1;
	}
	cout << fresh;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;

}