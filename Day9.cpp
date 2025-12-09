#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
#include <fstream>
#include <set>
#include <cmath>
#include <tuple>
#include <sstream>
using namespace std;
struct Cord {
	int col;
	int row;
};
void solve1() {
	ifstream fin("input.txt");
	string cord;
	vector<Cord> Cords;
	while (getline(fin, cord)) {
		Cord Cord;
		auto it = cord.find(",");
		if (it != string::npos) {
			Cord.col = stoll(cord.substr(0, it));
			Cord.row = stoll(cord.substr(it + 1, cord.size() - 1));
		}
		Cords.push_back(Cord);
	}
	long long maxvalue = 0;
	for (auto i = 0; i < Cords.size(); i++) {
		long long value;
		for (auto j = i + 1; j < Cords.size(); j++) {
			value = (llabs(Cords[i].col - Cords[j].col) + 1) * (llabs(Cords[i].row - Cords[j].row) + 1);
			maxvalue = max(maxvalue, value);
		}
	}
	cout << maxvalue;

}
void solve2() {
	ifstream fin("input.txt");
	string cord;
	vector<pair<long long, long long>> coordonate;
	while (getline(fin, cord)) {
		auto it = cord.find(",");
		if (it != string::npos) {
			long long x = stoll(cord.substr(0, it));
			long long y = stoll(cord.substr(it + 1, cord.size() - 1));
			coordonate.push_back(make_pair(x, y));
		}
	}

	int n = coordonate.size();
	vector<tuple<long long, long long, long long>> h_segments;
	vector<tuple<long long, long long, long long>> v_segments;

	for (int i = 0; i < n; i++) {
		long long x1 = coordonate[i].first;
		long long y1 = coordonate[i].second;
		long long x2 = coordonate[(i + 1) % n].first;
		long long y2 = coordonate[(i + 1) % n].second;
		if (y1 == y2) {
			h_segments.push_back({ y1, min(x1, x2), max(x1, x2) });
		}
		else {
			v_segments.push_back({ x1, min(y1, y2), max(y1, y2) });
		}
	}

	auto ray_casting = [&](long long X, long long Y) {
		bool inside = false;
		for (int i = 0, j = n - 1; i < n; j = i++) {
			long long x_i = coordonate[i].first;
			long long y_i = coordonate[i].second;
			long long x_j = coordonate[j].first;
			long long y_j = coordonate[j].second;
			if (y_i == y_j)
				continue; 
			bool intersect = ((y_i > Y) != (y_j > Y)) &&
				(X < (x_j - x_i) * (double)(Y - y_i) / (y_j - y_i) + x_i);
			if (intersect)
				inside = !inside;
		}
		return inside;
	};

	auto pe_margine = [&](long long X, long long Y) {
		for (size_t i = 0; i < h_segments.size(); i++) {
			long long hy = get<0>(h_segments[i]);
			long long hx1 = get<1>(h_segments[i]);
			long long hx2 = get<2>(h_segments[i]);
			if (Y == hy && X >= hx1 && X <= hx2)
				return true;
		}
		for (size_t i = 0; i < v_segments.size(); i++) {
			long long vx = get<0>(v_segments[i]);
			long long vy1 = get<1>(v_segments[i]);
			long long vy2 = get<2>(v_segments[i]);
			if (X == vx && Y >= vy1 && Y <= vy2)
				return true;
		}
		return false;
	};

	auto inauntru_sau_margine = [&](long long X, long long Y) {
		return pe_margine(X, Y) || ray_casting(X, Y);
	};

	auto h_segment_inside = [&](long long y, long long x1, long long x2) {
		if (!inauntru_sau_margine(x1, y))
			return false;
		if (!inauntru_sau_margine(x2, y))
			return false;
		vector<long long> crossings;
		for (size_t i = 0; i < v_segments.size(); i++) {
			long long vx = get<0>(v_segments[i]);
			long long vy1 = get<1>(v_segments[i]);
			long long vy2 = get<2>(v_segments[i]);
			if (vx > x1 && vx < x2 && y >= vy1 && y <= vy2) {
				crossings.push_back(vx);
			}
		}
		sort(crossings.begin(), crossings.end());
		long long prev = x1;
		for (long long cx : crossings) {
			long long mid = (prev + cx) / 2;
			if (!inauntru_sau_margine(mid, y))
				return false;
			prev = cx;
		}
		long long mid = (prev + x2) / 2;
		if (!inauntru_sau_margine(mid, y))
			return false;
		return true;
	};

	auto v_segment_inside = [&](long long x, long long y1, long long y2) {
		if (!inauntru_sau_margine(x, y1))
			return false;
		if (!inauntru_sau_margine(x, y2))
			return false;
		vector<long long> crossings;
		for (size_t i = 0; i < h_segments.size(); i++) {
			long long hy = get<0>(h_segments[i]);
			long long hx1 = get<1>(h_segments[i]);
			long long hx2 = get<2>(h_segments[i]);
			if (hy > y1 && hy < y2 && x >= hx1 && x <= hx2) {
				crossings.push_back(hy);
			}
		}
		sort(crossings.begin(), crossings.end());
		long long prev = y1;
		for (long long cy : crossings) {
			long long mid = (prev + cy) / 2;
			if (!inauntru_sau_margine(x, mid))
				return false;
			prev = cy;
		}
		long long mid = (prev + y2) / 2;
		if (!inauntru_sau_margine(x, mid))
			return false;
		return true;
	};

	long long answer = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			long long x1 = coordonate[i].first, y1 = coordonate[i].second;
			long long x2 = coordonate[j].first, y2 = coordonate[j].second;
			long long x_Min = min(x1, x2);
			long long y_Min = min(y1, y2);
			long long x_Max = max(x1, x2);
			long long y_Max = max(y1, y2);
			if (!h_segment_inside(y_Min, x_Min, x_Max))
				continue;
			if (!h_segment_inside(y_Max, x_Min, x_Max))
				continue;
			if (!v_segment_inside(x_Min, y_Min, y_Max))
				continue;
			if (!v_segment_inside(x_Max, y_Min, y_Max))
				continue;
			long long arie = (x_Max - x_Min + 1) * (y_Max - y_Min + 1);
			answer = max(answer, arie);
		}
	}
	cout << answer;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;
}