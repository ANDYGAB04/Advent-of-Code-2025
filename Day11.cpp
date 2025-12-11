#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include <map>
#include <fstream>
#include <set>
#include <cmath>
#include <tuple>
#include <sstream>
using namespace std;

struct Device {
	string key;
	vector<string> value;
};

map<tuple<string, bool, bool>, long long> cache;

int dfs1(const string& current, const vector<Device>& Devices) {
	if (current == "out") {
		return 1;
	}
	auto it = find_if(Devices.begin(), Devices.end(), [&current](const Device& A) {
		return A.key == current;
	});
	int count = 0;
	if (it != Devices.end()) {
		for (const auto& v : it->value) {
			count += dfs1(v, Devices);
		}
	}
	return count;
}

long long dfs2(const string& current, const vector<Device>& Devices, bool dac, bool fft) {
	if (current == "dac") {
		dac = true;
	}
	if (current == "fft") {
		fft = true;
	}
	if (current == "out") {
		return (fft && dac) ? 1 : 0;
	}
	
	auto cacheKey = make_tuple(current, dac, fft);
	auto cacheIt = cache.find(cacheKey);
	if (cacheIt != cache.end()) {
		return cacheIt->second;
	}
	
	auto it = find_if(Devices.begin(), Devices.end(), [&current](const Device& A) {
		return A.key == current;
	});
	long long count = 0;
	if (it != Devices.end()) {
		for (const auto& v : it->value) {
			count += dfs2(v, Devices, dac, fft);
		}
	}
	
	cache[cacheKey] = count;
	return count;
}

void solve1() {
	ifstream fin("input.txt");
	string Dev;
	vector<Device> Devices;
	while (getline(fin, Dev)) {
		Device d;
		Dev = Dev + " ";
		while (!Dev.empty()) {
			auto it = Dev.find(":");
			if (it != string::npos) {
				d.key = Dev.substr(0, it);
				Dev.erase(0, it + 2);
			}
			else {
				it = Dev.find(" ");
				if (it != string::npos) {
					d.value.push_back(Dev.substr(0, it));
					Dev.erase(0, it + 1);
				}
			}
		}
		Devices.push_back(d);
	}
	auto You = find_if(Devices.begin(), Devices.end(), [](Device& A) {
		return A.key == "you";
	});
	int count = 0;
	for (const auto& y : You->value) {
		count += dfs1(y, Devices);
	}
	cout << count << endl;
}

void solve2() {
	cache.clear();
	ifstream fin("input.txt");
	string Dev;
	vector<Device> Devices;
	while (getline(fin, Dev)) {
		Device d;
		Dev = Dev + " ";
		while (!Dev.empty()) {
			auto it = Dev.find(":");
			if (it != string::npos) {
				d.key = Dev.substr(0, it);
				Dev.erase(0, it + 2);
			}
			else {
				it = Dev.find(" ");
				if (it != string::npos) {
					d.value.push_back(Dev.substr(0, it));
					Dev.erase(0, it + 1);
				}
			}
		}
		Devices.push_back(d);
	}
	auto You = find_if(Devices.begin(), Devices.end(), [](Device& A) {
		return A.key == "svr";
	});
	long long count = 0;
	for (const auto& y : You->value) {
		count += dfs2(y, Devices, false, false);
	}
	cout << count << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;
}
