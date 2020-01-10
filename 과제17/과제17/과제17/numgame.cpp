#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main() {

	int T, k, num[100], strike[100], ball[100], arr[4], temp[4], check_strike=0, check_ball=0, check=0, cnt = 0;
	int can[4][10]; //can은 가능한 숫자를 저장하는 배열
	int total_can[100] = { 0, };

	ifstream input_fp("numgame.inp");
	ofstream output_fp("numgame.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> k;
		cnt = 0, check_strike = 0, check_ball = 0;
		for (int i = 0; i < 4; i++) { //can배열 초기화
			for (int j = 0; j < 10; j++) {
				can[i][j] = j;
			}
		}
		for (int i = 0; i < k; i++) { //가능한(can)배열 생성
			input_fp >> num[i] >> strike[i] >> ball[i];
			arr[0] = num[i] / 1000;
			arr[1] = (num[i] % 1000) / 100;
			arr[2] = (num[i] % 1000 % 100) / 10;
			arr[3] = num[i] % 1000 % 100 % 10;
			if (strike[i] == 0 && ball[i] >= 0) {
				if(can[0][arr[0]] != 0) can[0][arr[0]] = 0;
				if(can[1][arr[1]] != 0) can[1][arr[1]] = 0;
				if(can[2][arr[2]] != 0) can[2][arr[2]] = 0;
				if(can[3][arr[3]] != 0) can[3][arr[3]] = 0;
			}
		}
		for (int i = 1234; i <= 9876; i++) { //가능한 수 찾기
			check = 0, check_strike = 0, check_ball = 0;
			temp[0] = i / 1000;
			temp[1] = (i % 1000) / 100;
			temp[2] = (i % 1000 % 100) / 10;
			temp[3] = i % 1000 % 100 % 10;
			if (can[0][temp[0]] != 0 && can[1][temp[1]] != 0 && can[2][temp[2]] != 0 && can[3][temp[3]] != 0) {
				if (temp[0]!=temp[1] && temp[0]!=temp[2] && temp[0]!=temp[3] && temp[1]!=temp[2] && temp[1]!=temp[3] && temp[2]!=temp[3]) {
					for (int j = 0; j < k; j++) {
						arr[0] = num[j] / 1000;
						arr[1] = (num[j] % 1000) / 100;
						arr[2] = (num[j] % 1000 % 100) / 10;
						arr[3] = num[j] % 1000 % 100 % 10;
						if (temp[0] == arr[0]) check_strike++;
						if (temp[1] == arr[1]) check_strike++;
						if (temp[2] == arr[2]) check_strike++;
						if (temp[3] == arr[3]) check_strike++;
						if (temp[0] != arr[0] && (temp[0] == arr[1] || temp[0] == arr[2] || temp[0] == arr[3])) check_ball++;
						if (temp[1] != arr[1] && (temp[1] == arr[0] || temp[1] == arr[2] || temp[1] == arr[3])) check_ball++;
						if (temp[2] != arr[2] && (temp[2] == arr[0] || temp[2] == arr[1] || temp[2] == arr[3])) check_ball++;
						if (temp[3] != arr[3] && (temp[3] == arr[0] || temp[3] == arr[1] || temp[3] == arr[2])) check_ball++;
						if (strike[j] != check_strike || ball[j] != check_ball) break;
						if (strike[j] == check_strike && ball[j] == check_ball)
							check_strike = 0, check_ball = 0, check++;
					}
				}
			}
			if (check == k) { //모든 조건이 만족하면
				cnt++; 
				total_can[cnt-1] = i; 
			}
		}
		if (cnt <= 6) {
			output_fp << cnt << endl;
			for (int i = 0; i < cnt; i++) {
				output_fp << total_can[i] << endl;
			}
		}
		else if (cnt > 6) {
			sort(total_can, total_can + cnt);
			output_fp << cnt << endl;
			for (int i = 0; i < 3; i++)
				output_fp << total_can[i] << endl;
			for (int i = cnt - 3; i < cnt; i++)
				output_fp << total_can[i] << endl;
		}
	}
	input_fp.close();
	output_fp.close();
}