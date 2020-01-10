#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
#pragma warning (disable:4996)
vector<int> start;
vector<int> end1;
vector<int> year;
bool compare(int a, int b) {
	return a < b;
}

int main() {

	int T, N, s1, s2, s3, e1, e2, e3, row, max, start_check, end_check, i=1, j=0, check;
	char c1, c2, c3, c4;

	ifstream input_fp("timeline.inp");
	ofstream output_fp("timeline.out");

	input_fp >> T;
	for (int a = 0; a < T; a++) {
		input_fp >> N;
		for (int b = 0; b < N; b++) { //º¤ÅÍ »ý¼º
			input_fp >> s1 >> c1 >> s2 >> c2 >> s3 >> e1 >> c3 >> e2 >> c4 >> e3;
			s1 = s1 * 10000, s2 = s2 * 100;
			e1 = e1 * 10000, e2 = e2 * 100;
			start.push_back(s1 + s2 + s3), end1.push_back(e1 + e2 + e3);
			year.push_back(s1 + s2 + s3), year.push_back(e1 + e2 + e3);
		}
		sort(start.begin(), start.end(), compare);
		sort(end1.begin(), end1.end(), compare);
		sort(year.begin(), year.end(), compare);
		row = 1, max = 1, start_check = 1, end_check = 0;
		for (int b = 1; b < year.size(); b++) {
			check = 0;
 			if (i < start.size() && j < end1.size()) {
				if (b < year.size() - 1 && year[b] == year[b + 1] && start[i] == year[b] && end1[j] == year[b + 1]) {
					if (start.size() > i) i++;
					if (end1.size() > j) j++;
					start_check = 0, end_check = 1;
					if (b == year.size() - 2) break;
					check = 1, b++;
				}
			}
			if (check==0 && i < start.size()) {
				if (start_check == 1 && start[i] == year[b]) {
					row++;
					if (row > max) max++;
					if (start.size() > i) i++;
				}
				else if (end_check == 1 && start[i] == year[b]) {
					row++, start_check = 1, end_check = 0;
					if (row > max) max++;
					if (start.size() > i) i++;
				}
			}
			if (check == 0 && j < end1.size()) {
				if (start_check == 1 & end1[j] == year[b]) {
					row--, start_check = 0, end_check = 1;
					if (end1.size() > j) j++;
				}
				else if (end_check == 1 && end1[j] == year[b]) {
					row--;
					if (end1.size() > j) j++;
				}
			}
		}
		output_fp << max << endl;
		start.clear(), end1.clear(), year.clear(), i=1, j=0;
	}
	input_fp.close();
	output_fp.close();
}