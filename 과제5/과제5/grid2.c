#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {

	int num, row, col, type, dic, dis;
	int temp = 0, totaltemp = 0, result = 0, n = 1;
	int rowtemp = 0, coltemp = 0;
	int squareFirstNum = 0, firstNumDis = 0, squareSecondNum = 0, secondNumDis = 0;
	int squareThirdNum = 0, thirdNumDis = 0, squareFourthNum = 0, fourthNumDis = 0;

	FILE *input_fp = fopen("grid2.inp", "rt");
	FILE *output_fp = fopen("grid2.out", "wt");

	fscanf(input_fp, "%d", &num);

	for (int i = 0; i < num; i++) {
		fscanf(input_fp, "%d %d %d %d %d", &row, &col, &type, &dic, &dis);
		rowtemp = row, coltemp = col;
		for (;;) { //n값 구하기
			temp = 2 * rowtemp + 2 * coltemp - 4;
			totaltemp = totaltemp + temp;
			if (dis <= totaltemp) {
				break;
			}
			rowtemp = rowtemp - 2;
			coltemp = coltemp - 2;
			n++;
		}
		if (type == 3) { //타입 3
			if (dic == 1) { //좌상
				squareFirstNum = col * (n - 1) + n;
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum + coltemp - 1;
				secondNumDis = firstNumDis + coltemp - 1;

				squareThirdNum = squareSecondNum + col * (rowtemp - 1);
				thirdNumDis = secondNumDis + rowtemp - 1;

				squareFourthNum = squareThirdNum - coltemp + 1;
				fourthNumDis = thirdNumDis + coltemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum + (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum + col * (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum - dis + thirdNumDis;
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum - (col * (dis - fourthNumDis));
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 2) { //우상
				squareFirstNum = col * n - (n-1);
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum + col * (rowtemp - 1);
				secondNumDis = firstNumDis + rowtemp - 1;

				squareThirdNum = squareSecondNum - coltemp + 1;
				thirdNumDis = secondNumDis + coltemp - 1;

				squareFourthNum = squareThirdNum - (col * (rowtemp - 1));
				fourthNumDis = thirdNumDis + rowtemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum + col * (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum - dis + secondNumDis;
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum - (col * (dis - thirdNumDis));
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum + (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 3) { //우하
				squareFirstNum = col * row - ((col + 1) * (n - 1));
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum - coltemp + 1;
				secondNumDis = firstNumDis + coltemp - 1;

				squareThirdNum = squareSecondNum - col * (rowtemp - 1);
				thirdNumDis = secondNumDis + rowtemp - 1;

				squareFourthNum = squareThirdNum + coltemp - 1;
				fourthNumDis = thirdNumDis + coltemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum - dis + firstNumDis;
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum - (col * (dis - secondNumDis));
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum + (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum + col * (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 4) { //좌하
				squareFirstNum = col * row - ((col + 1) * (n - 1)) - coltemp + 1;
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum - (col*(rowtemp - 1));
				secondNumDis = firstNumDis + rowtemp - 1;

				squareThirdNum = squareSecondNum + coltemp - 1;
				thirdNumDis = secondNumDis + coltemp - 1;

				squareFourthNum = squareThirdNum + (col*(rowtemp-1));
				fourthNumDis = thirdNumDis + rowtemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum - (col * (dis - firstNumDis));
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum + (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum + col * (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum - dis + fourthNumDis;
					fprintf(output_fp, "%d\n", result);
				}
			}
		}
		if (type == 4) { //타입 4
			if (dic == 1) { //좌상
				squareFirstNum = col * (n - 1) + n;
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum + col * (rowtemp - 1);
				secondNumDis = firstNumDis + rowtemp - 1;

				squareThirdNum = squareSecondNum + coltemp - 1;
				thirdNumDis = secondNumDis + coltemp - 1;

				squareFourthNum = squareThirdNum - (col*(rowtemp-1));
				fourthNumDis = thirdNumDis + rowtemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum + col * (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum + (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum - col * (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum - (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 2) { //우상
				squareFirstNum = col * n - (n - 1);
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum - (coltemp - 1);
				secondNumDis = firstNumDis + coltemp - 1;

				squareThirdNum = squareSecondNum + (col*(rowtemp-1));
				thirdNumDis = secondNumDis + rowtemp - 1;

				squareFourthNum = squareThirdNum + coltemp - 1;
				fourthNumDis = thirdNumDis + coltemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum - (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum + col * (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum + (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum - col * (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 3) { //우하
				squareFirstNum = col * row - ((col + 1) * (n - 1));
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum - (col*(rowtemp - 1));
				secondNumDis = firstNumDis + rowtemp - 1;

				squareThirdNum = squareSecondNum - coltemp + 1;
				thirdNumDis = secondNumDis + coltemp - 1;

				squareFourthNum = squareThirdNum + (col*(rowtemp - 1));
				fourthNumDis = thirdNumDis + rowtemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum - col * (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum - (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum + col * (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum + (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
			if (dic == 4) { //좌하
				squareFirstNum = col * row - ((col + 1) * (n - 1)) - coltemp + 1;
				firstNumDis = totaltemp - temp + 1;

				squareSecondNum = squareFirstNum + coltemp - 1;
				secondNumDis = firstNumDis + coltemp - 1;

				squareThirdNum = squareSecondNum - (col*(rowtemp - 1));
				thirdNumDis = secondNumDis + rowtemp - 1;

				squareFourthNum = squareThirdNum - coltemp + 1;
				fourthNumDis = thirdNumDis + coltemp - 1;

				if (dis < secondNumDis) { //사각형의 첫째줄
					result = squareFirstNum + (dis - firstNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < thirdNumDis) { //사각형의 둘째줄
					result = squareSecondNum - col * (dis - secondNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else if (dis < fourthNumDis) { //사각형의 셋째줄
					result = squareThirdNum - (dis - thirdNumDis);
					fprintf(output_fp, "%d\n", result);
				}
				else { //사각형의 넷째줄
					result = squareFourthNum + col * (dis - fourthNumDis);
					fprintf(output_fp, "%d\n", result);
				}
			}
		}
		totaltemp = 0;
		n = 1;
	}
	fclose(input_fp);
	fclose(output_fp);
}