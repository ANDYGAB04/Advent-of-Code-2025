#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
#include <set>
using namespace std;

void solve1() {

	vector<vector<string>> mattrix(141, vector<string>(141));
	string row;
	
		for (long long i = 0; i < 141; i++) {
			getline(cin, row);
			for (long long j = 0; j < 141; j++) {
				mattrix[i][j] = row[j];
			}
		}
		long long splits = 0;
		for (long long i = 1; i < 141; i++) {
			for (long long j = 0; j < 141; j++) {
				if (mattrix[i][j] == "." && mattrix[i - 1][j] == "S") {
					mattrix[i][j] = "|";
				}
				else if (mattrix[i][j] == "." && mattrix[i - 1][j] == "|") {
					mattrix[i][j] = "|";
				}
				else if (mattrix[i][j] == "^" && mattrix[i - 1][j] == "|") {
					splits++;
					mattrix[i][j-1] = "|";
					mattrix[i][j+1] = "|";
				}
			}
		}
		cout << splits << endl;
		
	
}

void solve2() {
	vector<vector<string>> mattrix(141, vector<string>(141));
	string row;
	
	for (long long i = 0; i < 141; i++) {
		getline(cin, row);
		for (long long j = 0; j < 141; j++) {
			mattrix[i][j] = row[j];
		}
	}
	
	long long startCol = -1;
	for (long long j = 0; j < 141; j++) {
		if (mattrix[0][j] == "S") {
			startCol = j;
			break;
		}
	}
	
	map<long long, long long> blocks;
	blocks[startCol] = 1;
	
	for (long long i = 0; i < 140; i++) {
		map<long long, long long> nextBlocks;
		
		for (auto& p : blocks) {
			long long col = p.first;
			long long value = p.second;
			
			if (i + 1 < 141) {
				if (mattrix[i + 1][col] == "." || mattrix[i + 1][col] == "S") {
					nextBlocks[col] += value;
				}
				else if (mattrix[i + 1][col] == "^") {
					if (col - 1 >= 0) {
						nextBlocks[col - 1] += value;
					}
					if (col + 1 < 141) {
						nextBlocks[col + 1] += value;
					}
				}
			}
		}
		
		blocks = nextBlocks;
	}
	
	long long totalValue = 0;
	for (auto& p : blocks) {
		totalValue += p.second;
	}
	
	cout << endl << "Total: " << totalValue << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;
}
