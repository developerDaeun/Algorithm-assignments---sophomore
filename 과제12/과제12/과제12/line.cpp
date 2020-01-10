#include <iostream>
#include <fstream>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	long long int T, M, Q, A, cnt, check, k, min, max, temp, start, end, totalStart, totalEnd;

	ifstream input_fp("line.inp");
	ofstream output_fp("line.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) { //총 테스트 케이스 수
		input_fp >> M;
		cnt = 0, check = 0, temp = 0, min = 0, max = 0, totalStart = 0, totalEnd = 0;

		for (int b = 0; b < M; b++) { //질문하는 횟수
			temp = 0; //temp는 앞의 max값
			input_fp >> Q >> A;
			if (A > 1) {
				check++;
				//최솟값, 최댓값 구하기
				for (int i = 1; i < A; i++) {
					min = temp + 1;
					max = min + i - 1;
					temp = max;
				}
				start = (Q - max) / A;
				if ((Q - max) % A != 0) start++;
				if (A != 1) end = (Q - min) / (A - 1);
				if (check==1) { //첫번째 질문일때
					totalStart = start, totalEnd = end;
				}
				else { //두번째 질문부터 모두 다
					if (start >= totalStart && start <= totalEnd)
						totalStart = start;
					if (end <= totalEnd && end >= totalStart)
						totalEnd = end;
					if (totalEnd - totalStart == 0) {
						k = totalStart, cnt++;
						output_fp << cnt << " " << k << endl;
						break;
					}
				}
			}
			cnt++;
		}
		if (totalEnd - totalStart == 0) {
			for (int i = 0; i < M - cnt; i++)
				input_fp >> Q >> A;
			cnt--;
		}
		if (cnt == M) {
			output_fp << "-1" << endl;
		}
	}
	input_fp.close();
	output_fp.close();
}
