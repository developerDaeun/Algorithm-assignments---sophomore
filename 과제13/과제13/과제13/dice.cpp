#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	int N, num, start, before, temp, max, max2, totalMax = 0, dice[10000][6];
	ifstream input_fp("dice.inp");
	ofstream output_fp("dice.out");

	input_fp >> N;
	for (int i = 0; i < N; i++) { //배열 생성
		for (int j = 0; j < 6; j++) {
			input_fp >> num;
			dice[i][j] = num;
		}
	}
	for (int a = 0; a < 6; a++) {
		start = dice[0][a];
		if (a == 0 || a == 5) { //1번 주사위 max값 구하기
			max = dice[0][1];
			for (int c = 2; c < 5; c++)
				if (max < dice[0][c]) max = dice[0][c];
		}
		else if (a == 1 || a == 3) {
			max = dice[0][0];
			for (int c = 2; c < 6; c++) {
				if (c!=3 && max < dice[0][c]) max = dice[0][c];
			}
		}
		else if (a == 2 || a == 4) {
			max = dice[0][0];
			for (int c = 1; c < 6; c++) {
				if (c != 2 && c != 4 && max < dice[0][c]) max = dice[0][c];
			}
		}
		for (int i = 1; i < N; i++) { //1번이 아닌 나머지 주사위
			for (int k = 0; k < 6; k++) { 
				if (dice[i][k] == start) { //start와 before값 구하기
					if (k == 0) { before = start; start = dice[i][5]; break; }
					if (k == 1) { before = start; start = dice[i][3]; break; }
					if (k == 2) { before = start; start = dice[i][4]; break; }
					if (k == 3) { before = start; start = dice[i][1]; break; }
					if (k == 4) { before = start; start = dice[i][2]; break; }
					if (k == 5) { before = start; start = dice[i][0]; break; }
				}
			}
			temp = 0, max2 = 0;
			for (int j = 0; j < 6; j++) {
				if(dice[i][j] != start && dice[i][j] != before){
						temp = dice[i][j];
						if (max2 == 0) max2 = temp; 
				}
				if (max2 != temp && temp > max2)
					max2 = temp;
			}
			max = max + max2;
		}
		if (a == 0) { totalMax = max; } //최종값
		else {
			if (totalMax < max)
				totalMax = max;
		}
	}
	output_fp << totalMax;

	input_fp.close();
	output_fp.close();
}