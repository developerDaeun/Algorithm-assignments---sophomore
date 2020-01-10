#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<int, int> > edge;
vector<int> cnt;
vector<pair<int, int> > leaf;

int main() {

	int T, n, num1, num2, L, check, min = 0, temp, sum, sub;

	ifstream input_fp("tree.inp");
	ofstream output_fp("tree.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> n;
		edge.push_back(pair<int, int>(0, 0)); //edge 0 인덱스 초기화
		cnt.push_back(0);
		for (int i = 1; i < n; i++) {
			input_fp >> num1 >> num2;
			edge.push_back(make_pair(num1,num2)); //first:부모노드, second:가중치
			cnt.push_back(0);
		}
		for (int i = 1; i < n; i++) { //leaf노드 벡터 생성
			check = 0;
			for (int j = 1; j < n; j++) {
				if (i == edge[j].first) { check = 1; break; }
			}
			if (check == 0) leaf.push_back(make_pair(0, i));
		}
		for (int i = 0; i < leaf.size(); i++) { //각 L값 저장
			temp = leaf[i].second, sum = 0;
			while (1) {
				sum += edge[temp].second;
				if (edge[temp].first == 0) { 
					leaf[i].first = sum;
					break; 
				}
				temp = edge[temp].first;
			}
		}
		sort(leaf.begin(), leaf.end(), greater<pair<int, int> >());
		L = leaf[0].first;
		for (int i = 0; i < leaf.size(); i++) {
			sub = L;
			temp = leaf[i].second;
			int store = temp;
			while (1) {
				if (cnt[temp] == 0)
					cnt[temp] = 1, store = temp;
				sub -= edge[temp].second;
				if (edge[temp].first == 0) {
					edge[store].second += sub;
					min += sub;
					break;
				}
				temp = edge[temp].first;
			}
		}
		output_fp << min << endl;
		edge.clear(), leaf.clear(), cnt.clear(), min=0;
	}
	input_fp.close(), output_fp.close();
}