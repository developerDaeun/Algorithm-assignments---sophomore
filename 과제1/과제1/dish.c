#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {

	int num1 = 0;
	int num2 = 0;
	char c1, c2;
	int sum = 0;

	FILE *input_fp = fopen("dish.inp","rt");
	FILE *output_fp = fopen("dish.out", "wt");

	fscanf(input_fp, "%d", &num1);

	if (num1 <= 0) return 0;
	
	for (int i = 0; i < num1; i++) {
		fscanf(input_fp, "%d", &num2);
		if (num2 >= 3 && num2 <= 1000) {
			sum += 10;

			while (1) {
				fscanf(input_fp, "%c", &c1);
				if (c1 == '\n')
					continue;
				else
					break;
			}

			for (int j = 0; j < num2 - 1; j++) {
				fscanf(input_fp, "%c", &c2);
				if (c1 == c2) {
					sum += 5;
					c1 = c2;
					continue;
				}
				else if (c1 != c2) {
					sum += 10;
					c1 = c2;
				}
			}
			fprintf(output_fp, "%d\n", sum);
			sum = 0;
		}
	}

	fclose(input_fp);
	fclose(output_fp);
}