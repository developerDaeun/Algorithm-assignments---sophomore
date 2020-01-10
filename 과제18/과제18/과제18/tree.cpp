#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#pragma warning (disable : 4996)
using namespace std;

vector<long long int> parent;
vector<long long int> child;
bool check(long long int a, long long int b) {
	return a < b;
}
int main() {

	long long int start, end, root = 0, check1 = 0;

	ifstream input_fp("tree.inp");
	ofstream output_fp("tree.out");

	for (int a = 1;; a++) {
		input_fp >> start >> end;
		if (start == -1 && end == -1) break;
		if(start==0 && end==0) input_fp >> start >> end;
		parent.push_back(start);
		child.push_back(end);
		while (1) { //벡터 생성
			input_fp >> start >> end;
			if (start == 0 && end == 0) break;
			parent.push_back(start);
			child.push_back(end);
		}
		sort(parent.begin(), parent.end(), check);
		sort(child.begin(), child.end(), check);
		for (int i = 0; i < child.size()-1; i++) { //자식 비교
			if (child[i] == child[i + 1]) {
				check1 = 1, root = -1;
				break;
			}
		}
		if (check1 != 1) { //부모 비교
			int j = 0;
			for (int i = 0; i < child.size(); ) {
				if (parent.size() - 1 == j) i++;
				else if (parent[j] == parent[j + 1]) j++;
				else if (child[i] == parent[j]) j++;
				else if (child[i] < parent[j]) i++;
				else if (child[i] > parent[j]){
					if (root == 0) {
						root = parent[j];
						j++;
					}
					else {
						root = -1;
						break;
					}
				}
				if (i == child.size() - 1 && j == parent.size() - 1 && root != 0) {
					if (child[i] < parent[j]) {
						root = -1;
						break;
					}
				}
			}
		}
		if (root == 0) root = -1;
		output_fp << "Test Case " << a << ": " << root << endl;
		check1 = 0, root = 0, parent.clear(), child.clear();
	}

	input_fp.close();
	output_fp.close();
}