#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#pragma warning(disable : 4996)
using namespace std;

int main() {

	int n, leave, temp, quoleave, row = 0, col = 0, coltemp = 26, check = 1, cnt = 1, b, d, rxcycheck = 0, find[1000] = {0,};
	int last = 0, aaa=0, temp1;
	char die;
	string s;
	char c;

	ifstream input_fp("spreadsheet.inp");
	ofstream output_fp("spreadsheet.out");

	input_fp >> n;
	getline(input_fp, s);
	for (int a = 0; a < n; a++) {
		row = 0, col = 0, coltemp = 26, check = 1, cnt = 1, rxcycheck = 0, last = 0, aaa = 0;
		getline(input_fp, s);
		if (s[0] == 'R') { //RXCY ����
			if (!(s[1] > 64 && s[1] < 91)) {
				for (b = 0;; b++) { //RXCY�������� �Ǻ��ϱ�
					if (s[b] == 'C') break;
					if (s[b] == NULL) { rxcycheck++; break; }
					if(b>=2) check++;
				}
				if (!(rxcycheck == 1)) { //RXCY�����̸�
					last++;
					int k = check - 1;
					for (int c = 1; c <= check; c++) { //�౸�ϱ�
						if (check == c) { row = row + (s[c] - 48); break; }
						row = row + ((s[c] - 48) * pow(10,k));
						k--;
					}
					check = 0;
					for (d = b + 1;; d++) { //�����ϱ�
						if (s[d] == NULL) break;
						check++;
					}
					k = check - 1;
					for (int c = b + 1; c <= check + b; c++) { 
						if (check + b == c) { col = col + (s[c] - 48); break; }
						col = col + ((s[c] - 48) * pow(10,k));
						k--;
					}
					temp = col;
					leave = temp % 26;
					while (1) { //���° �ڸ��� ����(cnt) ���ϱ�
						quoleave = temp % 26;
						if (quoleave == 0) leave = 26;
						temp = temp / 26;
						if (temp == 26) { cnt++; break; }
						if (temp == 0) break;
						cnt++;
					}
					temp = col;
					while (1) { //���۰� ù������ ���ϱ�
						temp = temp / 26;
						if (temp >= 0 && temp <= 26) break;
						leave = temp % 26;
					}
					if (cnt == 1) { //���ڰ� �ϳ��̸�
						if (leave == 0) leave = 26; 
						c = leave + 64; 
						output_fp << c; 
					} 
					else if(cnt == 2){ //���ڰ� �ΰ��̸�
						if (leave == 0 || leave == 26) { temp--; leave = 26; }
						if (temp != 0) {
							c = temp + 64;
							output_fp << c;
						}
						c = leave + 64;
						output_fp << c;
					}
					else { //���ڰ� �����̻�
						temp = col;
						for (int c = 0;c<cnt; c++) { //�迭 ����
							find[c] = temp % 26;
							temp = temp / 26;
						}
						for (b = 0; b < cnt; b++) {
							if (b == cnt - 1 && find[cnt - 2] != 0 && find[cnt - 1] == 0) {
								find[b] = 26;
								aaa = 2;
								break;
							}
							if ((find[b] == 0 && b != cnt - 1)) {
								temp1 = 0;
								find[b] = 26;
								aaa++;
								break;
							}
						}
						if (aaa == 1) { //0�� ��������
							for (d = b + 1; d < cnt; d++) {
								if (temp1 == 0) {
									if (find[d] == 0) temp1 = 0;
									else temp1 = find[d];
									find[d] = find[d] - 1;
									if (find[d] == 0) temp1 = 0;
									if (find[d] <= 0) find[d] = find[d] + 26;
								}
								else {
									if (find[d] == 0) temp1 = 0;
									temp1 = find[d];
								}
							}
							if ((find[cnt-1] == 0 || find[cnt - 1] == 26) && find[cnt-2] == 26) cnt--;
						}
						for (int e = cnt-1; e >= 0; e--) {
							c = find[e] + 64;
							if (find[e] == 0) c = 90;
							output_fp << c;
						}
					}
					output_fp << row << endl;
				}
			}
		}
		if(last==0) { //������
			check = 0;
			for (int c = 0;; c++) { //�� ���۹�ȣ ���ϱ�
				if (!(s[c] > 64 && s[c] < 91)) break;
				check++;
			}
			output_fp << 'R';
			for (int c = check;; c++) { //�� ���
				if (s[c] == NULL) break;
				output_fp << s[c] - 48;
			}
			if (check == 1) output_fp << 'C' << s[0] - 64 << endl;  //���ڰ� �ϳ��̸�
			else if(check == 2) { //���ڰ� �ΰ��̸�
				temp = 26 * (s[0] - 64) + s[1] - 64;
				output_fp << 'C' << temp << endl;
			} 
			else { //���ڰ� �����̻�
				temp = 26 * (s[0] - 64) + s[1] - 64;
				for (int c = 2; c < check; c++)
					temp = temp * 26 + s[c] - 64;
				output_fp << 'C' << temp << endl;
			}
		}
	}
	input_fp.close();
	output_fp.close();
}