#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {
	int T, N, num, cnt = 0, arr[6] = { 0, };
	int codenum[8][6] = { {0,0,0,0,0,0},{0,0,1,1,1,1},{0,1,0,0,1,1},{0,1,1,1,0,0},{1,0,0,1,1,0},{1,0,1,0,0,1},{1,1,0,1,0,1},{1,1,1,0,1,0} };
	char codechar[8] = { 'A','B','C','D','E','F','G','H' };
	FILE *input_fp = fopen("mail.inp", "rt");
	FILE *output_fp = fopen("mail.out", "wt");
	fscanf(input_fp, "%d", &T);
	for (int i = 0; i < T; i++) { //T개만큼
		fscanf(input_fp, "%d", &N);
		for (int j = 0; j < N; j++) { //N개만큼
			for (int k = 0; k < 6; k++) {
				fscanf(input_fp, "%1d", &num);
				arr[k] = num;
			}
			for (int r = 0; r <= 8; r++) {
				if (r == 8) {
					fprintf(output_fp, "%c", 'X');
					break;
				}
				for (int s = 0; s < 6; s++)
					if (arr[s] == codenum[r][s]) cnt++;
				if (cnt == 5 || cnt == 6) {
					fprintf(output_fp, "%c", codechar[r]);
					break;
				}
				cnt = 0;
			}
			cnt = 0;
		}
		fprintf(output_fp, "\n");
	}
	fclose(input_fp);
	fclose(output_fp);
}