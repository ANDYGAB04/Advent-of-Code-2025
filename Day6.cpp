#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stack>
#include<map>
#include <set>
using namespace std;

void solve1() {

	vector<vector<string>> mattrix(5, vector<string>(1000));
	for (long long i = 0; i < 5; i++) {
		for (long long j = 0; j < 1000; j++) {
			cin >> mattrix[i][j];
		}
	}
	long long finalsum = 0;
	for (long long j = 0; j < 1000; j++) {
		long long colsum = 0;
		long long colpro = 1;
		for (long long i = 0; i < 4; i++) {
			if (mattrix[4][j] == "*")
			{
				colpro *= stoll(mattrix[i][j]);
			}
			else
			{
				colsum += stoll(mattrix[i][j]);
			}
		}
		if (mattrix[4][j] == "*") {
			finalsum += colpro;
		}
		else
		finalsum += colsum;
	}
	cout << finalsum << endl;
}

void solve2() {
	vector<string> dataRows;
	string inputLine;
	string opLine;
	
	while (getline(cin, inputLine)) {
		bool containsOnlyOperators = true;
		for (char ch : inputLine) {
			if (ch != ' ' && ch != '+' && ch != '*') {
				containsOnlyOperators = false;
				break;
			}
		}
		
		if (containsOnlyOperators) {
			opLine = inputLine;
			break;
		}
		dataRows.push_back(inputLine);
	}
	
	int rowCount = dataRows.size();
	int colCount = dataRows[0].size();
	long long result = 0;

	vector<long long> numberBuffer;
	char operation = 0;
	
	for (int col = colCount - 1; col >= 0; col--) {
		bool emptyCol = true;
		string colDigits = "";
		
		for (int row = 0; row < rowCount; row++) {
			char ch = dataRows[row][col];
			if (ch != ' ') {
				emptyCol = false;
			}
			if (isdigit(ch)) {
				colDigits += ch;
			}
		}
		
		char op = opLine[col];
		
		if (emptyCol && op == ' ') {
			if (!numberBuffer.empty()) {
				long long tempResult = 0;
				if (operation == '+') {
					for (long long val : numberBuffer) {
						tempResult += val;
					}
					result += tempResult;
				} else if (operation == '*') {
					tempResult = 1;
					for (long long val : numberBuffer) {
						tempResult *= val;
					}
					result += tempResult;
				}
				numberBuffer.clear();
				operation = 0;
			}
			continue;
		}
		
		if (!colDigits.empty()) {
			long long value = stoll(colDigits);
			numberBuffer.push_back(value);
		}
		
		if (op == '+' || op == '*') {
			operation = op;
		}
	}
	
	if (!numberBuffer.empty()) {
		long long tempResult = 0;
		if (operation == '+') {
			for (long long val : numberBuffer) {
				tempResult += val;
			}
			result += tempResult;
		} else if (operation == '*') {
			tempResult = 1;
			for (long long val : numberBuffer) {
				tempResult *= val;
			}
			result += tempResult;
		}
	}
	
	cout << result << endl;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;
}
