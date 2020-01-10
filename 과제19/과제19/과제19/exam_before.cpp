#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#pragma warning (disable : 4996)
using namespace std;

int main() {
	
	int T, n, check[100] = { 0, }, star_length = 0, star_check=0, start, end, bad=0;
	string set, P, Q;
	vector<char> v1;
	vector<char> v2;

	ifstream input_fp("exam.inp");
	ofstream output_fp("exam.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		output_fp << "Test Case: #" << a + 1 << endl;
		input_fp >> set >> P >> n;
		for (int b = 0; b < set.length(); b++) {
			v1.push_back(set[b]);
		}
		for (int b = 0; b < n; b++) { //각 질의어 비교
			input_fp >> Q;
			for (int i = 0; i < P.length(); i++) {
				if (P[i] == '*') {
					star_length = Q.length() - (P.length() - 1);
					start = i, end = i + star_length - 1;
					star_check = 1;
					i++;
					if (star_length == 0) star_check = 2;
				}
				if (star_check == 0) {
					if (P[i] != '?' && P[i] != '*' && P[i] != Q[i]) {
						check[b] = 1;
						break;
					}
					if (P[i] == '?') {
						v2.push_back(Q[i]);
						if (!includes(v1.begin(), v1.end(), v2.begin(), v2.end())) {
							check[b] = 1;
							break;
						}
					}
				}
				if (star_check == 1) {
					if (P[i] != '?' && P[i] != Q[i + star_length - 1]) {
						check[b] = 1;
						break;
					}
					if (P[i] == '?') {
						v2.push_back(Q[i + star_length - 1]);
						if (!includes(v1.begin(), v1.end(), v2.begin(), v2.end())) { 
							check[b] = 1; 
							break; 
						}
					}
				}
				if (star_check == 2) {
					if (P[i] != '?' && P[i] != Q[i - 1]) {
						check[b] = 1;
						break;
					}
					if (P[i] == '?') {
						v2.push_back(Q[i - 1]);
						if (!includes(v1.begin(), v1.end(), v2.begin(), v2.end())) {
							check[b] = 1;
							break;
						}
					}
				}
			}
			if (star_check == 1) {
				for (int i = start; i <= end; i++) {
					v2.push_back(Q[i]);
					if (!includes(v1.begin(), v1.end(), v2.begin(), v2.end())) {
						bad++;
					}
				}
				if (bad == 0) check[b] = 1;
			}
			star_check = 0, bad = 0, v1.clear(), v2.clear();
		}
		for (int b = 0; b < n; b++) { //0이면 Yes, 1이면 No 출력
			if (check[b] == 0) output_fp << "Yes" << endl; 
			else output_fp << "No" << endl;
		}
		for (int b = 0; b < 100; b++) { //check배열 초기화
			if(check[b]==1) check[b] = 0;
		}
	}
	input_fp.close();
	output_fp.close();
}