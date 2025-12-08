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
using namespace std;

struct Cord {
	long long X;
	long long Y;
	long long Z;
};

class UnionFind {
private:
	vector<int> parent;
	vector<int> size;
	
public:
	UnionFind(int n) {
		parent.resize(n);
		size.resize(n, 1);
		for (int i = 0; i < n; i++) {
			parent[i] = i;
		}
	}
	
	int find(int x) {
		if (parent[x] != x) {
			parent[x] = find(parent[x]); 
		}
		return parent[x];
	}
	
	bool unite(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);
		
		if (rootX == rootY) {
			return false; 
		}
		
		
		if (size[rootX] < size[rootY]) {
			parent[rootX] = rootY;
			size[rootY] += size[rootX];
		} else {
			parent[rootY] = rootX;
			size[rootX] += size[rootY];
		}
		return true;
	}
	
	int getSize(int x) {
		return size[find(x)];
	}
	
	vector<int> getAllSizes() {
		set<int> roots;
		for (int i = 0; i < parent.size(); i++) {
			roots.insert(find(i));
		}
		vector<int> sizes;
		for (int root : roots) {
			sizes.push_back(size[root]);
		}
		return sizes;
	}
};

long long distanceSquared(const Cord& a, const Cord& b) {
	long long dx = a.X - b.X;
	long long dy = a.Y - b.Y;
	long long dz = a.Z - b.Z;
	return dx * dx + dy * dy + dz * dz;
}

void solve1() {
	ifstream fin("input.txt");
	vector<Cord> Cords;
	long long x, y, z;
	char c;
	while (fin >> x >> c >> y >> c >> z) {
		Cords.push_back({x, y, z});
	}
	
	int n = Cords.size();
	UnionFind uf(n);
	
	vector<tuple<long long, int, int>> edges;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			long long dist = distanceSquared(Cords[i], Cords[j]);
			edges.push_back(make_tuple(dist, i, j));
		}
	}
	
	
	sort(edges.begin(), edges.end(), [](const tuple<long long, int, int>& a, const tuple<long long, int, int>& b) {
		if (get<0>(a) != get<0>(b))
			return get<0>(a) < get<0>(b);
		if (get<1>(a) != get<1>(b))
			return get<1>(a) < get<1>(b);
		return get<2>(a) < get<2>(b);
	});
	
	for (int i = 0; i < 10; i++) {
		int node1 = get<1>(edges[i]);
		int node2 = get<2>(edges[i]);
		
		if (uf.find(node1) != uf.find(node2)) {
			uf.unite(node1, node2);
		}
	}
	
	
	vector<int> sizes = uf.getAllSizes();
	sort(sizes.rbegin(), sizes.rend()); 
	
	for (int s : sizes) {
		cout << s << " ";
	}
	cout << endl;
	
	if (sizes.size() >= 3) {
		long long result = (long long)sizes[0] * sizes[1] * sizes[2];
		cout << "Product of three largest circuits: " << result << endl;
	}
}

void solve2() {
	ifstream fin("input.txt");
	vector<Cord> Cords;
	long long x, y, z;
	char c;
	while (fin >> x >> c >> y >> c >> z) {
		Cords.push_back({x, y, z});
	}
	
	int n = Cords.size();
	UnionFind uf(n);
	
	vector<tuple<long long, int, int>> edges;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			long long dist = distanceSquared(Cords[i], Cords[j]);
			edges.push_back(make_tuple(dist, i, j));
		}
	}
	
	sort(edges.begin(), edges.end(), [](const tuple<long long, int, int>& a, const tuple<long long, int, int>& b) {
		if (get<0>(a) != get<0>(b))
			return get<0>(a) < get<0>(b);
		if (get<1>(a) != get<1>(b))
			return get<1>(a) < get<1>(b);
		return get<2>(a) < get<2>(b);
	});
	
	int lastNode1 = -1, lastNode2 = -1;
	int numCircuits = n;
	
	for (size_t i = 0; i < edges.size(); i++) {
		int node1 = get<1>(edges[i]);
		int node2 = get<2>(edges[i]);
		
		if (uf.find(node1) != uf.find(node2)) {
			uf.unite(node1, node2);
			lastNode1 = node1;
			lastNode2 = node2;
			numCircuits--;
			
			
			if (numCircuits == 1) {
				break;
			}
		}
	}
	
	if (lastNode1 != -1 && lastNode2 != -1) {
		long long result = Cords[lastNode1].X * Cords[lastNode2].X;
		cout << result << endl;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	//solve1();
	solve2();
	return 0;
}
