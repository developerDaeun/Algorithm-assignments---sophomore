#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	int T, N, M, num, arr1[50][50] = { 0, }, arr2[50][50] = { 0, }, temp, check;

	ifstream input_fp("paper.inp");
	ofstream output_fp("paper.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> N >> M;
		for (int i = 0; i < N; i++) { //세로무늬 배열 생성
			for (int j = 0; j < M - 1; j++) {
				input_fp >> num;
				arr1[i][j] = num;
			}
		}
		for (int i = 0; i < N - 1; i++) { //가로무늬 배열 생성
			for (int j = 0; j < M; j++) {
				input_fp >> num;
				arr2[i][j] = num;
			}
		}
		while (1) {
			for (int i = 0; i < M - 1; i++) {
				for (int j = 0; j < N - 1; j++) {
					temp = arr1[j][i] + arr1[j+1][i] + arr2[j][i] + arr2[j][i+1];
					if (temp == 1 || temp == 3) {
						check = 0;
					}
					else { check = 1; break; }
				}
				if (check == 1) break;
			}
			if (check == 0) { output_fp << "1 "; break; }
			else { output_fp << "0 "; break; }
		}
	}
	input_fp.close();
	output_fp.close();
}

