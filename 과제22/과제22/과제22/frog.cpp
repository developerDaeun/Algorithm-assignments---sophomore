#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	int T, N, D, M, dis[100] = { 0, }, B_cnt = 0, S_cnt = 0, max=0;
	char S, stone[100];

	ifstream input_fp("frog.inp");
	ofstream output_fp("frog.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> N >> D;
		for (int b = 0; b < N; b++) { //stone과 dis 배열 생성
			input_fp >> stone[b] >> dis[b];
			dis[b] = -dis[b];
			if (stone[b] == 'B') B_cnt++;
			if (stone[b] == 'S') S_cnt++;
		}
		if (B_cnt > 0 && S_cnt == 0) { //B만 있을 때
			if (dis[0] >= (D-dis[B_cnt - 1])) max = dis[0];
			else max = D - dis[B_cnt - 1];
			if (B_cnt > 1) {
				for (int i = 0; i < B_cnt - 1; i++) {
					if (max < dis[i + 1] - dis[i]) max = dis[i + 1] - dis[i];
				}
			}
		}
		else if (B_cnt == 0 && S_cnt > 0) { //S만 있을 때
			if (S_cnt == 1) max = D;
			else {
				if (dis[1] >= (D - dis[S_cnt - 2])) max = dis[1];
				else max = D - dis[S_cnt - 2];
			}
			if (S_cnt > 2) {
				for (int i = 0; i < S_cnt - 2; i++) {
					if (max < dis[i + 2] - dis[i]) max = dis[i + 2] - dis[i];
				}
			}
		}
		else { //B, S 둘다 있을 때
			if (stone[0] == 'B' && stone[N - 1] == 'B') {
				if (dis[0] >= D - dis[N - 1]) max = dis[0];
				else max = D - dis[N - 1];
			}
			else if (stone[0] == 'B' && stone[N - 1] != 'B') {
				if (dis[0] >= D - dis[N - 2]) max = dis[0];
				else max = D - dis[N - 2];
			}
			else if (stone[0] != 'B' && stone[N - 1] == 'B') {
				if (dis[1] >= D - dis[N - 1])max = dis[1];
				else max = D - dis[N - 1];
			}
			else {
				if (dis[1] >= D - dis[N - 2]) max = dis[1];
				else max = D - dis[N - 2];
			}
			for (int i = 0; i < N - 2; i++) {
				if (stone[i + 1] != 'B' && max < dis[i + 2] - dis[i]) 
					max = dis[i + 2] - dis[i];
				else if (stone[i + 1] == 'B') {
					if (max < dis[i + 1] - dis[i]) max = dis[i + 1] - dis[i];
					if (max < dis[i + 2] - dis[i + 1]) max = dis[i + 2] - dis[i + 1];
				}
			}
		}
		output_fp << "Case " << a + 1 << ": " << max << endl;
		for (int b = 0; b < 100; b++) { //stone과 dis 배열 초기화
			if (dis[b] != 0) dis[b] = 0;
			if (stone[b] == 'B' || stone[b] == 'S') stone[b] = NULL;
		}
		B_cnt = 0, S_cnt = 0, max = 0;
	}
	input_fp.close();
	output_fp.close();
}