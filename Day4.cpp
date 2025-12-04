#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
using namespace std;
void solve1() {
	string row;
	vector<vector<string>> mattrix(148 +2,vector<string>(148+2));
	int rows = 0;
	int cols = 0;
	for (auto j = 0; j < 148; j++) {
		mattrix[0][j] = ".";
		mattrix[147][j] = ".";
	}
	for (auto i = 0; i < 148; i++) {
		mattrix[i][0] = ".";
		mattrix[i][147] = ".";
	}
	int i = 1;
	while (getline(cin,row)) {
		if (row == "") {
			break;
		}
		for (auto j = 0; j < row.size(); j++) {
			mattrix[i][j+1] = row[j];
		}
		i++;
		cols = row.size();
		rows++;

	}
	int nrpaper = 0;
	for (int i = 1; i <= rows; i++) {
		for (int j = 1; j <= cols; j++) {
			if (mattrix[i][j] == "@" ) {
				int nrofar = 0;
				for (int l = i - 1; l <= i + 1; l++){
					for (int k = j - 1; k <= j + 1; k++) {
						if (k == j && l == i) {
							continue;
						}
						else if (mattrix[l][k] == "@") {
							nrofar++;
							}
						
					}
				}
				if (nrofar < 4) {
					nrpaper++;
				}
				
			}
		}
	}
	cout << nrpaper << endl;
	

}
void solve2() {
	string row;
	vector<vector<string>> mattrix(148 + 2, vector<string>(148 + 2));
	int rows = 0;
	int cols = 0;
	for (auto j = 0; j < 148; j++) {
		mattrix[0][j] = ".";
		mattrix[147][j] = ".";
	}
	for (auto i = 0; i < 148; i++) {
		mattrix[i][0] = ".";
		mattrix[i][147] = ".";
	}
	int i = 1;
	while (getline(cin, row)) {
		if (row == "") {
			break;
		}
		for (auto j = 0; j < row.size(); j++) {
			mattrix[i][j + 1] = row[j];
		}
		i++;
		cols = row.size();
		rows++;

	}
	int nrpaper = 0;
	bool modificari = true;
	while (modificari == true) {
		vector<pair<int, int>> poz;
		bool ok = false;
		for (int i = 1; i <= rows; i++) {
			for (int j = 1; j <= cols; j++) {
				if (mattrix[i][j] == "@") {
					int nrofar = 0;
					for (int l = i - 1; l <= i + 1; l++) {
						for (int k = j - 1; k <= j + 1; k++) {
							if (k == j && l == i) {
								continue;
							}
							else if (mattrix[l][k] == "@") {
								nrofar++;
							}

						}
					}
					if (nrofar < 4) {
						ok = true;
						nrpaper++;
						poz.push_back({ i, j });
					}

				}
			}
		}
		for (auto it : poz) {
			mattrix[it.first][it.second] = ".";
		}
		if (ok == false) {
			break;
		}
	}
	cout << nrpaper << endl;


}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;

}