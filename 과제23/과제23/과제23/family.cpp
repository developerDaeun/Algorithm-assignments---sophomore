#include <iostream>
#include <fstream>
#include <vector>
#pragma warning (disable : 4996)
using namespace std;

vector<int> temp[500001];
vector<int> family[500001];
vector<int> arr[500001];
int main() {

	int T, N, parent, child, root, start, max=0;

	ifstream input_fp("family.inp");
	ofstream output_fp("family.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> N;
		for (int i = 0; i < N-1; i++) {
			input_fp >> parent >> child;
			temp[child].push_back(parent);
			family[parent].push_back(child);
		}
		root = child;
		while(temp[root].size()!=0) { //루트 찾기
			root = temp[root][0];
		}
		arr[1].push_back(root);
		for (int i = 1; ; i++) {
			if (arr[i].size() == 0) break;
			for (int j = 0; j < arr[i].size(); j++) {
				start = arr[i][j];
				for (int k = 0; k < family[start].size(); k++) {
					arr[i + 1].push_back(family[start][k]);
				}
			}
			max++;
		}
		output_fp << max << endl;
		max = 0;
		for (int i = 1; i < 500001; i++) {
			temp[i].clear();
			family[i].clear();
			arr[i].clear();
		}
	}
	input_fp.close();
	output_fp.close();
}