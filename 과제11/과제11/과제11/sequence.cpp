#include <iostream>
#include <fstream>
#include <stdio.h>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	long long int A, L, result, cnt;

	ifstream input_fp("sequence.inp");
	ofstream output_fp("sequence.out");

	int i = 1;
	while (1) {
		input_fp >> A >> L;
		result = A, cnt = 1;
		if (A < 0) break;
		else {
			while (1) {
				if (result % 2 == 0) { result = result / 2; cnt++; }
				else { result = 3 * result + 1; cnt++; }
				if (result == 1) break;
				if (result > L) { cnt--; break; }
			}
			output_fp << "Case " << i << ": A = " << A << ", " << "limit = " << L << ", number of terms = " << cnt << endl;
		}
		i++;
	}
	input_fp.close();
	output_fp.close();
}