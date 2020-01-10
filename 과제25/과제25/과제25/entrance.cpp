#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#pragma warning (disable:4996)
vector<int> order;

int main() {

	int T, N, num, min, max, temp, arr[1000] = {0,};

	ifstream input_fp("entrance.inp");
	ofstream output_fp("entrance.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> N;
		for (int i = 0; i < N; i++)
			input_fp >> arr[i];
		order.push_back(arr[0]);
		for (int i = 1; i < N; i++) {
			for (int j = 0; j < order.size(); j++) { //최솟값 초기화
				if (arr[i] - order[j] > 0) {
					min = arr[i] - order[j]; break;
				}
				else min = 0;
			}
			for (int j = 0; j < order.size(); j++) {
				if (order[j] < arr[i]) {
					temp = arr[i] - order[j];
					if (temp <= min) { min = temp, order[j] = arr[i]; }
				}
			}
			if (min == 0)
				order.push_back(arr[i]);
		}
		output_fp << order.size() << '\n';
		for (int i = 0; i < N; i++) {
			if (arr[i] != 0) arr[i] = 0;
		}
		order.clear();
	}
	input_fp.close();
	output_fp.close();
}