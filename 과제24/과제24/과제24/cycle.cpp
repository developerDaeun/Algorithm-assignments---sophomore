#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#pragma warning (disable : 4996)
using namespace std;
vector<int> edge[1000000];
queue<int> que;

int main() {

	int T, n, m, start, end, first[1000000] = { 0, }, second[1000000] = { 0, };
	bool check = true;
	ifstream input_fp("cycle.inp");
	ofstream output_fp("cycle.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> n >> m;
		for (int i = 0; i < m; i++) {    //vector create
			input_fp >> start >> end;
			edge[start].push_back(end);
			edge[end].push_back(start);
		}
		first[0] = 1, que.push(0);                 //first, second array create
		for (int i = 0; i < edge[0].size(); i++) {
			second[edge[0][i]] = 1, que.push(edge[0][i]);
		}
		int temp;
		while (1) {
			que.pop();
			if (que.empty()) break;
			temp = que.front();
			for (int i = 0; i < edge[temp].size(); i++) {
				if((first[temp]==1 && second[edge[temp][i]]!=1) || (second[temp]==1 && first[edge[temp][i]]!=1))
					que.push(edge[temp][i]);
				if (first[temp] == 1) {
					if (first[edge[temp][i]] == 1) {
						check = false; break;
					}
					else if (second[edge[temp][i]] == 0) second[edge[temp][i]] = 1;
				}
				else if (second[temp] == 1) {
					if (second[edge[temp][i]] == 1) {
						check = false; break;
					}
					else if(first[edge[temp][i]] == 0) first[edge[temp][i]] = 1;
				}
			}
			if (check == false) break;
		}
		if (check == false) output_fp << "O" << endl;
		else output_fp << "X" << endl;

		for (int i = 0; i < n; i++)      //vector reset
			if (edge[i].size() != 0) edge[i].clear();
		for (int i = 0; i < 1000000; i++) {
			if (first[i] != 0) first[i] = 0;
			if (second[i] != 0) second[i] = 0;
		}
		while (!que.empty()) que.pop();
		check = true;
	}
	input_fp.close();
	output_fp.close();
}