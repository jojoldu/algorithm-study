#include <fstream>
#include <limits>
#include <iostream>
#include <vector>
#define DMAX 1001
using namespace std;

struct Edge{
	int source;
	int dest;
	int weight;
};

struct Result{
	int min;
	int max;
	bool isMin;
	bool isMax;

	void out(){
		if (min == numeric_limits<int>::max() || max == numeric_limits<int>::min()) {
			cout << "UNREACHABLE";
		}
		else{
			if (isMin) cout << min;
			else cout << "INFINITY";
			cout << " ";
			if (isMax) cout << max;
			else cout << "INFINITY";
		}
	}
};

Result TIMETRIP(Edge edges[], int edgeCount, int nodeCount, int source) {
	int i, j;
	Result result;
	int dmin[DMAX];
	int dmax[DMAX];
	for (i = 0; i < nodeCount; i++){
		if (i == source) dmin[i] = dmax[i] = 0;
		else {
			dmin[i] = numeric_limits<int>::max();
			dmax[i] = numeric_limits<int>::min();
		}
	}
	for (i = 0; i < nodeCount; i++){
		for (j = 0; j < edgeCount; j++){
			if (dmin[edges[j].dest] > dmin[edges[j].source] + edges[j].weight){
				if (dmin[edges[j].source] != numeric_limits<int>::max()) {
					dmin[edges[j].dest] = dmin[edges[j].source] + edges[j].weight;
				}
			}
			if (dmax[edges[j].dest] < dmax[edges[j].source] + edges[j].weight){
				if (dmax[edges[j].source] != numeric_limits<int>::min()) {
					dmax[edges[j].dest] = dmax[edges[j].source] + edges[j].weight;
				}
			}
		}
	}
	result.isMax = result.isMin = true;
	result.min = dmin[1];
	result.max = dmax[1];
	for (i = 0; i < edgeCount; i++){
		if (dmin[edges[i].dest] > dmin[edges[i].source] + edges[i].weight){
			result.isMin = false;
			break;
		}
	}
	for (i = 0; i < edgeCount; i++){
		if (dmax[edges[i].dest] < dmax[edges[i].source] + edges[i].weight){
			result.isMax = false;
			break;
		}
	}

	return result;
}

int main() {
	int cases, V, W, i;
	Edge edges[DMAX];
	cin >> cases;
	while (cases--){
		cin >> V >> W;
		for (i = 0; i < W; i++){
			cin >> edges[i].source >> edges[i].dest >> edges[i].weight;
		}
		TIMETRIP(edges, W, V, 0).out();
		cout << endl;
	}
	
	return 0;
}