#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#pragma warning (disable : 4996)
using namespace std;

priority_queue<int> q;

int main() {

	long long int N, num, cost, min1, min2, result[10000] = { 0, };

	ifstream input_fp("add.inp");
	ofstream output_fp("add.out");

	for(int a=0;;a++) {
		input_fp >> N;
		if (N == 0) break;
		for (int i = 0; i < N; i++) { //큐 생성
			input_fp >> num;
			q.push(-num);
		}
		for (int i = 0; i < N-1; i++) {
			min1 = -q.top(); //가장 작은값 리턴
			q.pop(); //가장 작은값 제거
			min2 = -q.top(); //두번째로 작은값 리턴
			q.pop(); //두번째 작은값 리턴
			cost = min1 + min2;
			q.push(-cost);
			result[a] = result[a] + cost;
		}
		q.pop();
	}
	for (int i = 0; ; i++) {
		if (result[i] == 0) break;
		output_fp << result[i] << endl;
	}
	input_fp.close();
	output_fp.close();
}