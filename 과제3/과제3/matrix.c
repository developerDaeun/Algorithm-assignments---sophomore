#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {

	int num;
	int n;
	int input;
	int arr[300][300] = { 0, };
	int i = 0, j = 0, p = 0, q = 0;
	int cnt1 = 0, cnt2 = 0;
	int temp = 0;
	int num1 = 0, num2 = 0;
	int truefalse = 0;

	FILE *input_fp = fopen("matrix.inp", "rt");
	FILE *output_fp = fopen("matrix.out", "wt");

	fscanf(input_fp, "%d", &num);
	for (int a = 0; a < num; a++) {
		fscanf(input_fp, "%d", &n);
		for (i = 1; i <= n; i++) { //행렬 생성
			for (j = 1; j <= n; j++) {
				fscanf(input_fp, "%d", &input);
				arr[i][j] = input;
			}
		}
		for (i = 1; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				//--모든 원소 비교하는 for문
				if (arr[i][j] != 1) {
					temp = arr[i][j];
					cnt1++;
					for (p = 1; p <= n; p++) {
						if (arr[i][p] != arr[i][j]) {
							num1 = arr[i][p];
							for (q = 1; q <= n; q++) {
								if (arr[q][j] != arr[i][j]) {
									num2 = arr[q][j];
									if (num1 + num2 == temp) {
										truefalse++;
										cnt2++;
										break;
									}
								}
							}
							if (truefalse == 1) {
								truefalse = 0;
								break;
							}
						}
					}
				}
			}
		}
		if (cnt1 == cnt2) fprintf(output_fp, "1\n");
		else fprintf(output_fp, "0\n");
		cnt1 = 0, cnt2 = 0;
	}
	fclose(input_fp);
	fclose(output_fp);
}