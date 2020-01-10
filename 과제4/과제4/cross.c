#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {

	int T, N, num;
	int arr1[10000], arr2[10000];
	int arr3[10000], arr4[10000];
	int cnt = 0, temp = 1;

	FILE *input_fp = fopen("cross.inp", "rt");
	FILE *output_fp = fopen("cross.out", "wt");

	fscanf(input_fp,"%d", &T);
	for (int a = 1; a <= T; a++) { //테스트케이스 수
		fscanf(input_fp, "%d", &N);
		for (int i = 1; i <= N; i++) { //S1 생성
			fscanf(input_fp, "%d", &num);
			arr1[i] = num;
			arr3[i] = i;
		}
		for (int j = 1; j <= N; j++) { //S2 생성
			fscanf(input_fp, "%d", &num);
			arr2[j] = num;
		}
		for (int p = 1; p <= N; p++) {
			for (int q = 1; q <= N; q++) {
				if (arr1[p] == arr2[q]) { //동일 숫자 찾기
					arr4[p] = q;
				}
			}
		}
		for (int r = 1; r <= N; r++) {
			for (int s = 1; s <= N; s++) {
				if (arr3[r] < arr3[s] && arr4[r] > arr4[s]) {
					cnt++;
				}
			}
		}
		fprintf(output_fp, "Case %d: %d\n", a, cnt);
		cnt = 0;
	}
	fclose(input_fp);
	fclose(output_fp);
}