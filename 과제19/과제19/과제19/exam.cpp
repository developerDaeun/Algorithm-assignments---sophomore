#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	int T, n, check[100] = { 0, }, star_length = 0, star_check = 0, start, end, bad = 0, temp=1;
	string set, P, Q;

	ifstream input_fp("exam.inp");
	ofstream output_fp("exam.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		output_fp << "Test Case: #" << a + 1 << endl;
		input_fp >> set >> P >> n;
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
						for (int j = 0; j < set.length(); j++) {
							if (Q[i] == set[j]) { temp = 0; break; }
						}
						if (temp == 1) {
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
						for (int j = 0; j < set.length(); j++) {
							if (Q[i + star_length - 1] == set[j]) { temp = 0; break; }
						}
						if (temp == 1) {
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
						for (int j = 0; j < set.length(); j++) {
							if (Q[i - 1] == set[j]) { temp = 0; break; }
						}
						if (temp == 1) {
							check[b] = 1;
							break;
						}
					}
				}
				temp = 1;
 			}
			if (star_check == 1) {
				for (int i = start; i <= end; i++) {
					for (int j = 0; j < set.length(); j++) {
						if (Q[i] != set[j]) bad = 1;
						if (Q[i] == set[j]) { bad = 0; break; }
					}
					if (bad == 1) break;
				}
				if (bad == 0) check[b] = 1;
			}
			star_check = 0, bad = 0, temp = 1;
		}
		for (int b = 0; b < n; b++) { //0이면 Yes, 1이면 No 출력
			if (check[b] == 0) output_fp << "Yes" << endl;
			else output_fp << "No" << endl;
		}
		for (int b = 0; b < 100; b++) { //check배열 초기화
			if (check[b] == 1) check[b] = 0;
		}
	}
	input_fp.close();
	output_fp.close();
}