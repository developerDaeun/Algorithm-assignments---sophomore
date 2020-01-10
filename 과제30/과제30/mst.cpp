#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
struct EDGE {
	int start;
	int end;
	int w;
};
vector<EDGE> weight;
vector<pair<int, int> > result;
int set[2][10000];
int total[10000] = { 0, };
bool compare(EDGE a, EDGE b) {
	return a.w < b.w;
}
bool compare2(pair<int, int> a, pair<int, int> b) {
	if (a.first == b.first) {
		return a.second < b.second;
	}
	return a.first < b.first;
}
int main() {

	int n, m, start, end, w; //n:정점개수, m:에지개수

	ifstream input_fp("mst.inp");
	ofstream output_fp("mst.out");

	input_fp >> n >> m;
	for (int i = 0; i < m; i++) {
		input_fp >> start >> end >> w;
		EDGE temp;
		temp.start = start, temp.end = end, temp.w = w;
		weight.push_back(temp);
	}
	sort(weight.begin(), weight.end(), compare);
	for (int i = 0; i < 10000; i++) {
		set[0][i] = 10001, set[1][i] = 1;
	}
	for (int i = 0; i < weight.size(); i++) {
		int temp = weight[i].start, index = weight[i].start;
		while (temp != 10001) {
			if(set[0][temp]!=10001) index = set[0][temp];
			temp = set[0][temp];
		}
		int temp2 = weight[i].end, index2 = weight[i].end;
		while(temp2 != 10001) {
			if (set[0][temp2]!=10001) index2 = set[0][temp2];
			temp2 = set[0][temp2];
		}
		if (index != index2) {
			if (set[1][index] >= set[1][index2]) {
				set[1][index] += set[1][index2];
				total[index] += weight[i].w;
				total[index] += total[index2];
				set[0][index2] = index;
			}
			else {
				set[1][index2] += set[1][index];
				total[index2] += weight[i].w;
				total[index2] += total[index];
				set[0][index] = index2;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (set[0][i] == 10001) {
			result.push_back(make_pair(set[1][i], total[i]));
		}
	}
	sort(result.begin(), result.end(), compare2);
	for (int i = 0; i < result.size(); i++) {
		output_fp << result[i].first << " " << result[i].second << endl;
	}
	input_fp.close(), output_fp.close();
}