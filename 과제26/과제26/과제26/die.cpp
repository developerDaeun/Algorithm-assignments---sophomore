#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#pragma warning (disable:4996)

int main() {

	int T, N, dice[6], temp[6], top_index, front_index, temp1, x=0, y=0;
	string d;

	ifstream input_fp("die.inp");
	ofstream output_fp("die.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		for (int i = 0; i < 6; i++) //[0]:top [1]:front [2]:바닥 [3]:동쪽 [4]:북쪽 [5]:서쪽
			input_fp >> dice[i];
		input_fp >> temp[0] >> temp[1] >> N >> d; //top, front
		for (int i = 0; i < 2; i++) { //temp 배열 만들기
				if (i == 0) {
					if (temp[0] == dice[0]) { temp[2] = dice[2]; top_index = 0; }
					else if (temp[0] == dice[2]) { temp[2] = dice[0]; top_index = 2; }
					else if (temp[0] == dice[1]) { temp[2] = dice[4]; top_index = 1; }
					else if (temp[0] == dice[4]) { temp[2] = dice[1]; top_index = 4; }
					else if (temp[0] == dice[3]) { temp[2] = dice[5]; top_index = 3; }
					else if (temp[0] == dice[5]) { temp[2] = dice[3]; top_index = 5; }
				}
				else {
					if (temp[1] == dice[0]) { temp[4] = dice[2]; front_index = 0; }
					else if (temp[1] == dice[2]) { temp[4] = dice[0]; front_index = 2; }
					else if (temp[1] == dice[1]) { temp[4] = dice[4]; front_index = 1; }
					else if (temp[1] == dice[4]) { temp[4] = dice[1]; front_index = 4; }
					else if (temp[1] == dice[3]) { temp[4] = dice[5]; front_index = 3; }
					else if (temp[1] == dice[5]) { temp[4] = dice[3]; front_index = 5; }
				}
		}
		if (top_index == 0) { //temp 배열 완성
			if (front_index == 1) temp[3] = dice[3], temp[5] = dice[5];
			else if (front_index == 3) temp[3] = dice[4], temp[5] = dice[1];
			else if (front_index == 4) temp[3] = dice[5], temp[5] = dice[3];
			else temp[3] = dice[1], temp[5] = dice[4];
		}
		else if (top_index == 1) {
			if (front_index == 0) temp[3] = dice[5], temp[5] = dice[3];
			else if (front_index == 2) temp[3] = dice[3], temp[5] = dice[5];
			else if (front_index == 3) temp[3] = dice[0], temp[5] = dice[2];
			else if (front_index == 5) temp[3] = dice[2], temp[5] = dice[0];
		}
		else if (top_index == 2) {
			if (front_index == 1) temp[3] = dice[5], temp[5] = dice[3];
			else if (front_index == 3) temp[3] = dice[1], temp[5] = dice[4];
			else if (front_index == 4) temp[3] = dice[3], temp[5] = dice[5];
			else if (front_index == 5) temp[3] = dice[4], temp[5] = dice[1];
		}
		else if (top_index == 3) {
			if (front_index == 0)temp[3] = dice[1], temp[5] = dice[4];
			else if (front_index == 1) temp[3] = dice[2], temp[5] = dice[0];
			else if (front_index == 2) temp[3] = dice[4], temp[5] = dice[1];
			else if (front_index == 4) temp[3] = dice[0], temp[5] = dice[2];
		}
		else if (top_index == 4) {
			if (front_index == 0)temp[3] = dice[3], temp[5] = dice[5];
			else if (front_index == 2) temp[3] = dice[5], temp[5] = dice[3];
			else if (front_index == 3) temp[3] = dice[2], temp[5] = dice[0];
			else if (front_index == 5) temp[3] = dice[0], temp[5] = dice[2];
		}
		else if (top_index == 5) {
			if (front_index == 0)temp[3] = dice[4], temp[5] = dice[1];
			else if (front_index == 1) temp[3] = dice[0], temp[5] = dice[2];
			else if (front_index == 2) temp[3] = dice[1], temp[5] = dice[4];
			else if (front_index == 4) temp[3] = dice[2], temp[5] = dice[0];
		}
		for (int i = 0; i < d.length(); i++) { 
			if (d[i] == 'E') { 
				x++; 
				temp1 = temp[5];
				temp[5] = temp[2], temp[2] = temp[3], temp[3] = temp[0], temp[0] = temp1;
			}
			else if (d[i] == 'W') { 
				x--; 
				temp1 = temp[3];
				temp[3] = temp[2], temp[2] = temp[5], temp[5] = temp[0], temp[0] = temp1;
			}
			else if (d[i] == 'S') {
				y--;
				temp1 = temp[0];
				temp[0] = temp[4], temp[4] = temp[2], temp[2] = temp[1], temp[1] = temp1;
			}
			else if (d[i] == 'N') {
				y++;
				temp1 = temp[1];
				temp[1] = temp[2], temp[2] = temp[4], temp[4] = temp[0], temp[0] = temp1;
			}
		}
		output_fp << x << " " << y << " " << temp[0] << " " << temp[1] << endl;
		x = 0, y = 0;
	}
	input_fp.close();
	output_fp.close();
}