#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)
int find(int arr[][1000], int i, int j, int N);

int main() {
	int T, N, num, arr[1000][1000];
	int cnt = 1;

	FILE *input_fp = fopen("block.inp", "rt");
	FILE *output_fp = fopen("block.out", "wt");

	fscanf(input_fp, "%d", &T);
	for (int a = 0; a < T; a++) {
		fscanf(input_fp, "%d", &N);
		for (int i = 0; i < N; i++) { //배열 생성
			for (int j = 0; j < i+1; j++) {
				fscanf(input_fp, "%d", &num);
				arr[i][j] = num;
			}
		}
		cnt = 1;

		while (cnt != 0) {
			cnt = 0;
			for (int i = N - 1; i > -1; i--) { //-1부분 찾기
				for (int j = i; j > -1; j--) {
					if (arr[i][j] == -1) {
						arr[i][j] = find(arr, i, j, N);
						if (arr[i][j] != -1) cnt++;
					}
				}
			}
			for (int i = 0; i < N; i++) {
				for (int j = i; j > -1; j--) {
					if (arr[i][j] == -1) {
						arr[i][j] = find(arr, i, j, N);
						if (arr[i][j] != -1) cnt++;
					}
				}
			}
		}
		for (int i = 0; i < N; i++) { //배열 출력
			for (int j = 0; j < i+1; j++) {
				fprintf(output_fp, "%d ", arr[i][j]);
			}
			fprintf(output_fp, "\n");
		}
		
	}
	fclose(input_fp);
	fclose(output_fp);
}
int find(int arr[][1000], int i, int j, int N) {
	int temp = 0;
	if (i == 0 && j == 0) { //꼭대기
		if (arr[1][0] != -1 && arr[1][1] != -1) {
			temp = (arr[1][0] + arr[1][1]) % 100;
			return temp;
		}
		else return -1;
	}
	else if (i == N - 1 && j == 0) { //맨 왼쪽 아래
		if (arr[N - 2][0] != -1 && arr[N - 1][1] != -1) {
			if (arr[N - 2][0] - arr[N - 1][1] < 0)
				temp = 100 + arr[N - 2][0] - arr[N - 1][1];
			else temp = arr[N - 2][0] - arr[N - 1][1];
			return temp;
		}
		else return -1;
	}
	else if (i == N - 1 && j == N - 1) { //맨 오른쪽 아래
		if (arr[N - 2][N - 2] != -1 && arr[N - 1][N - 2] != -1) {
			if (arr[N - 2][N - 2] - arr[N - 1][N - 2] < 0)
				temp = 100 + arr[N - 2][N - 2] - arr[N - 1][N - 2];
			else temp = arr[N - 2][N - 2] - arr[N - 1][N - 2];
			return temp;
		}
		else return -1;
	}
	else if (i > 0 && i < N - 1 && j == 0) { //맨 왼쪽 줄
		if (arr[i - 1][0] != -1 && arr[i][1] != -1) {
			if (arr[i - 1][0] - arr[i][1] < 0)
				temp = 100 + arr[i - 1][0] - arr[i][1];
			else temp = arr[i - 1][0] - arr[i][1];
			return temp;
		}
		if (arr[i + 1][0] != -1 && arr[i + 1][1] != -1) {
			temp = (arr[i + 1][0] + arr[i + 1][1]) % 100;
			return temp;
		}
		else return -1;
	}
	else if (i > 0 && i < N - 1 && i == j) { //맨 오른쪽 줄
		if (arr[i - 1][j - 1] != -1 && arr[i][j - 1] != -1) {
			if (arr[i - 1][j - 1] - arr[i][j - 1] < 0)
				temp = 100 + arr[i - 1][j - 1] - arr[i][j - 1];
			else temp = arr[i - 1][j - 1] - arr[i][j - 1];
			return temp;
		}
		if (arr[i + 1][j] != -1 && arr[i + 1][j + 1] != -1) {
			temp = (arr[i + 1][j] + arr[i + 1][j + 1]) % 100;
			return temp;
		}
		else return -1;
	}
	else if (i == N - 1 && j > 0 && j < N - 1) { //맨 아래 줄
		if (arr[i - 1][j - 1] != -1 && arr[i][j - 1] != -1) {
			if (arr[i - 1][j - 1] - arr[i][j - 1] < 0)
				temp = 100 + arr[i - 1][j - 1] - arr[i][j - 1];
			else temp = arr[i - 1][j - 1] - arr[i][j - 1];
			return temp;
		}
		if (arr[i - 1][j] != -1 && arr[i][j + 1] != -1) {
			if (arr[i - 1][j] - arr[i][j + 1] < 0)
				temp = 100 + arr[i - 1][j] - arr[i][j + 1];
			else temp = arr[i - 1][j] - arr[i][j + 1];
			return temp;
		}
		else return -1;
	}
	else { //나머지 모두
		if (arr[i - 1][j - 1] != -1 && arr[i][j - 1] != -1) {
			if (arr[i - 1][j - 1] - arr[i][j - 1] < 0)
				temp = 100 + arr[i - 1][j - 1] - arr[i][j - 1];
			else temp = arr[i - 1][j - 1] - arr[i][j - 1];
			return temp;
		}
		if (arr[i - 1][j] != -1 && arr[i][j + 1] != -1) {
			if (arr[i - 1][j] - arr[i][j + 1] < 0)
				temp = 100 + arr[i - 1][j] - arr[i][j + 1];
			else temp = arr[i - 1][j] - arr[i][j + 1];
			return temp;
		}
		if (arr[i + 1][j] != -1 && arr[i + 1][j + 1] != -1) {
			temp = (arr[i + 1][j] + arr[i + 1][j + 1]) % 100;
			return temp;
		}
		else return -1;
	}
}