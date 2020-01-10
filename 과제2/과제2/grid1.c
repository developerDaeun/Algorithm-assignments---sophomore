#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable : 4996)

int main() {

	int num = 0;
	int row=0, col=0;
	int type = 0, start = 0, dis = 0;
	int temp = 0;
	int quo = 0, leave = 0;

	FILE *input_fp = fopen("grid1.inp", "rt");
	FILE *output_fp = fopen("grid1.out", "wt");

	fscanf(input_fp, "%d", &num); //ù��°�� ��ĵ

	for (int i = 0; i < num; i++) {
		fscanf(input_fp, "%d", &row); //�� ��ĵ
		fscanf(input_fp, "%d", &col); //�� ��ĵ
		fscanf(input_fp, "%d", &type); //Ÿ�� ��ĵ
		fscanf(input_fp, "%d", &start); //������ ��ĵ
		fscanf(input_fp, "%d", &dis); //ã�� ��ġ ��ĵ
		
		// Ÿ�� 1
		if (type == 1) {
			quo = dis / col; //��
			leave = dis % col; //������
			if (leave == 0) {
				leave = col;
				quo = quo - 1;
			}
			if (start == 1) { //�»�
				if (quo % 2 == 1) {
					temp = (quo * col) + col - (leave - 1);
					fprintf(output_fp, "%d\n", temp);
				}
				else
					fprintf(output_fp, "%d\n", dis);
			}
			if (start == 2) { //���
				if (quo % 2 == 0) {
					temp = (quo + 1)*col - (leave - 1);
					fprintf(output_fp, "%d\n", temp);
				}
				else
					fprintf(output_fp, "%d\n", dis);
			}
			if (start == 3) { //����
				if (quo % 2 == 0) {
					temp = (row*col) - dis + 1;
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (row*col) + leave - (quo + 1)*col;
					fprintf(output_fp, "%d\n", temp);
				}
			}
			if (start == 4) { //����
				if (quo % 2 == 0) {
					temp = (row*col) + leave - (quo + 1)*col;
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (row*col) - dis + 1;
					fprintf(output_fp, "%d\n", temp);
				}
			}
		}

		//Ÿ��2
		if (type == 2) {
			quo = dis / row; //��
			leave = dis % row; //������
			if (leave == 0) {
				leave = row;
				quo = quo - 1;
			}
			if (start == 1) { //�»�
				if (quo % 2 == 0) {
					temp = (quo + 1) + (leave - 1)*col;
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (row*col) - (col-quo-1) - (col*(leave-1));
					fprintf(output_fp, "%d\n", temp);
				}
			}
			if (start == 2) { //���
				if (quo % 2 == 0) {
					temp = (col*leave) - quo;
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (row*col) - (quo + (col*(leave - 1)));
					fprintf(output_fp, "%d\n", temp);
				}
			}
			if (start == 3) { //����
				if (quo % 2 == 0) {
					temp = (row*col) - (quo+col*(leave-1));
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (col*leave) - quo;
					fprintf(output_fp, "%d\n", temp);
				}
			}
			if (start == 4) { //����
				if (quo % 2 == 0) {
					temp = (row*col) - ((col - quo - 1) + col*(leave - 1));
					fprintf(output_fp, "%d\n", temp);
				}
				else {
					temp = (quo + 1) + col * (leave - 1);
					fprintf(output_fp, "%d\n", temp);
				}
			}
		}
	}

	fclose(input_fp);
	fclose(output_fp);
}