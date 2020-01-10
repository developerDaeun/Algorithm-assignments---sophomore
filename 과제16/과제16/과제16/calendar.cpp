#include <iostream>
#include <fstream>
#include <string>
#pragma warning (disable : 4996)
using namespace std;

int main() {

	int type, year1, year2, month1, month2, day1, day2, cnt1, cnt2, leave1, leave2, temp, cnt, cntt, a;
	int totalDay1, totalDay2, total, MonthDay[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	string dayWeek1, dayWeek2;
	char c;

	ifstream input_fp("calendar.inp");
	ofstream output_fp("calendar.out");

	while (1) {
		input_fp >> type;
		if (type == -1) break;
		cnt = 0, cntt = 0;
		if (type == 0) { 
			input_fp >> year1 >> c >> month1 >> c >> day1;
			input_fp >> year2 >> c >> month2 >> c >> day2;
			totalDay1 = (year1 - 1) * 365 + day1;
			totalDay2 = (year2 - 1) * 365 + day2;
			for (int i = 1; i < month1; i++)
				totalDay1 = totalDay1 + MonthDay[i];
			for (int i = 1; i < month2; i++)
				totalDay2 = totalDay2 + MonthDay[i];
			if (year1 >= 4) { //윤년 계산 1 
				for (int i = 4; i <= year1; i = i + 4) {
					if (i == year1 && month1 < 3) break;
					if (i == year1 && month1 > 2 && (i % 100 != 0 || i % 400 == 0)) {
							totalDay1 = totalDay1 + 1;
							break;
					}
					if (i % 100 != 0 || i%400 == 0)
						totalDay1 = totalDay1 + 1;
				}
			}
			if (year2 >= 4) { //윤년 계산 2
				for (int i = 4; i <= year2; i = i + 4) {
					if (i == year2 && month2 < 3) break;
					if (i == year2 && month2 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay2 = totalDay2 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay2 = totalDay2 + 1;
				}
			}
			if (month1 == 2 && day1 > 28 && (year1 % 4 != 0 || (year1 % 100 == 0 && year1 % 400 != 0)))
				output_fp << "-1" << endl;
			else if (month2 == 2 && day2 > 28 && (year2 % 4 != 0 || (year2 % 100 == 0 && year2 % 400 != 0)))
					output_fp << "-1" << endl;
			else if (month1 !=2 && MonthDay[month1] < day1)
				output_fp << "-1" << endl;
			else if(month2 !=2 && MonthDay[month2] < day2)
				output_fp << "-1" << endl;
			else {
				if (totalDay1 > totalDay2)
					total = totalDay1 - totalDay2;
				else
					total = totalDay2 - totalDay1;
				output_fp << total << endl;
			}
		}
		else if (type == 1) {
			input_fp >> year1 >> c >> month1 >> c >> day1;
			input_fp >> year2 >> c >> month2 >> c >> cnt2 >> c >> dayWeek2;
			if (dayWeek2 == "Mon") leave2 = 0;
			if (dayWeek2 == "Tue") leave2 = 1;
			if (dayWeek2 == "Wed") leave2 = 2;
			if (dayWeek2 == "Thu") leave2 = 3;
			if (dayWeek2 == "Fri") leave2 = 4;
			if (dayWeek2 == "Sat") leave2 = 5;
			if (dayWeek2 == "Sun") leave2 = 6;
			totalDay1 = (year1 - 1) * 365 + day1;
			totalDay2 = (year2 - 1) * 365;
			for (int i = 1; i < month1; i++)
				totalDay1 = totalDay1 + MonthDay[i];
			for (int i = 1; i < month2; i++)
				totalDay2 = totalDay2 + MonthDay[i];
			if (year1 >= 4) { //윤년 계산 1
				for (int i = 4; i <= year1; i = i + 4) {
					if (i == year1 && month1 < 3) break;
					if (i == year1 && month1 > 2 && (i%100!=0 || i%400==0)) {
						totalDay1 = totalDay1 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay1 = totalDay1 + 1;
				}
			}
			if (year2 >= 4) { //윤년 계산 2
				for (int i = 4; i <= year2; i = i + 4) {
					if (i == year2 && month2 < 3) break;
					if (i == year2 && month2 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay2 = totalDay2 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay2 = totalDay2 + 1;
				}
			}
			temp = totalDay2 % 7; // 7로 나눴을때 나머지 구하기 (그 달의 첫번째 요일)
			totalDay2++;
			if (temp == 6 && temp > leave2)
				leave2 = leave2 + temp + 1;
			else if (temp > leave2)
				leave2 = leave2 + 7;
			a = MonthDay[month2] + temp;
			if (month2 == 2 && (year2 % 4 == 0 && (year2 % 100 != 0 || year2 % 400 == 0)))
				a++;
			for (int i = temp; i < a; i++) {
				if (i == leave2) {
					leave2 = leave2 + 7;
					cnt++;
				}
				if (cnt == cnt2) break;
				totalDay2++;
			}
			if (cnt != cnt2 || (month1 == 2 && day1 > 28 && (year1 % 4 != 0 || (year1 % 100 == 0 && year1 % 400 != 0))))
					output_fp << "-1" << endl;
			else if (month1 != 2 && MonthDay[month1] < day1)
				output_fp << "-1" << endl;
			else {
				if (totalDay1 > totalDay2)
					total = totalDay1 - totalDay2;
				else
					total = totalDay2 - totalDay1;
				output_fp << total << endl;
			}
		}
		else if (type == 2) {
			input_fp >> year1 >> c >> month1 >> c >> cnt1 >> c >> dayWeek1;
			input_fp >> year2 >> c >> month2 >> c >> day2;
			if (dayWeek1 == "Mon") leave1 = 0;
			if (dayWeek1 == "Tue") leave1 = 1;
			if (dayWeek1 == "Wed") leave1 = 2;
			if (dayWeek1 == "Thu") leave1 = 3;
			if (dayWeek1 == "Fri") leave1 = 4;
			if (dayWeek1 == "Sat") leave1 = 5;
			if (dayWeek1 == "Sun") leave1 = 6;
			totalDay1 = (year1 - 1) * 365;
			totalDay2 = (year2 - 1) * 365 + day2;
			for (int i = 1; i < month1; i++)
				totalDay1 = totalDay1 + MonthDay[i];
			for (int i = 1; i < month2; i++)
				totalDay2 = totalDay2 + MonthDay[i];
			if (year1 >= 4) { //윤년 계산 1
				for (int i = 4; i <= year1; i = i + 4) {
					if (i == year1 && month1 < 3) break;
					if (i == year1 && month1 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay1 = totalDay1 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay1 = totalDay1 + 1;
				}
			}
			if (year2 >= 4) { //윤년 계산 2
				for (int i = 4; i <= year2; i = i + 4) {
					if (i == year2 && month2 < 3) break;
					if (i == year2 && month2 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay2 = totalDay2 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay2 = totalDay2 + 1;
				}
			}
			temp = totalDay1 % 7; // 7로 나눴을때 나머지 구하기 (그 달의 첫번째 요일)
			totalDay1++;
			if (temp == 6 && temp > leave1)
				leave1 = leave1 + temp + 1;
			else if (temp > leave1)
				leave1 = leave1 + 7;
			a = MonthDay[month1] + temp;
			if (month1 == 2 && (year1 % 4 == 0 && (year1 % 100 != 0 || year1 % 400 == 0)))
				a++;
			for (int i = temp; i < a; i++) {
				if (i == leave1) {
					leave1 = leave1 + 7;
					cnt++;
				}
				if (cnt == cnt1) break;
				totalDay1++;
			}
			if (cnt != cnt1 || (month2 == 2 && day2 > 28 && (year2 % 4 != 0 || (year2 % 100 == 0 && year2 % 400 != 0))))
					output_fp << "-1" << endl;
			else if (month2!=2 && MonthDay[month2] < day2)
				output_fp << "-1" << endl;
			else {
				if (totalDay1 > totalDay2)
					total = totalDay1 - totalDay2;
				else
					total = totalDay2 - totalDay1;
				output_fp << total << endl;
			}
		}
		else if (type == 3) {
			input_fp >> year1 >> c >> month1 >> c >> cnt1 >> c >> dayWeek1;
			input_fp >> year2 >> c >> month2 >> c >> cnt2 >> c >> dayWeek2;
			if (dayWeek1 == "Mon") leave1 = 0;
			if (dayWeek1 == "Tue") leave1 = 1;
			if (dayWeek1 == "Wed") leave1 = 2;
			if (dayWeek1 == "Thu") leave1 = 3;
			if (dayWeek1 == "Fri") leave1 = 4;
			if (dayWeek1 == "Sat") leave1 = 5;
			if (dayWeek1 == "Sun") leave1 = 6;
			if (dayWeek2 == "Mon") leave2 = 0;
			if (dayWeek2 == "Tue") leave2 = 1;
			if (dayWeek2 == "Wed") leave2 = 2;
			if (dayWeek2 == "Thu") leave2 = 3;
			if (dayWeek2 == "Fri") leave2 = 4;
			if (dayWeek2 == "Sat") leave2 = 5;
			if (dayWeek2 == "Sun") leave2 = 6;
			totalDay1 = (year1 - 1) * 365;
			totalDay2 = (year2 - 1) * 365;
			for (int i = 1; i < month1; i++)
				totalDay1 = totalDay1 + MonthDay[i];
			for (int i = 1; i < month2; i++)
				totalDay2 = totalDay2 + MonthDay[i];
			if (year1 >= 4) { //윤년 계산 1
				for (int i = 4; i <= year1; i = i + 4) {
					if (i == year1 && month1 < 3) break;
					if (i == year1 && month1 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay1 = totalDay1 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay1 = totalDay1 + 1;
				}
			}
			if (year2 >= 4) { //윤년 계산 2
				for (int i = 4; i <= year2; i = i + 4) {
					if (i == year2 && month2 < 3) break;
					if (i == year2 && month2 > 2 && (i % 100 != 0 || i % 400 == 0)) {
						totalDay2 = totalDay2 + 1;
						break;
					}
					if (i % 100 != 0 || i % 400 == 0)
						totalDay2 = totalDay2 + 1;
				}
			}
			temp = totalDay1 % 7; // 7로 나눴을때 나머지 구하기 (그 달의 첫번째 요일)
			totalDay1++;
			if (temp == 6 && temp > leave1)
				leave1 = leave1 + temp + 1;
			else if (temp > leave1)
				leave1 = leave1 + 7;
			a = MonthDay[month1] + temp;
			if (month1 == 2 && (year1 % 4 == 0 && (year1 % 100 != 0 || year1 % 400 == 0)))
				a++;
			for (int i = temp; i < a; i++) {
				if (i == leave1) {
					leave1 = leave1 + 7;
					cnt++;
				}
				if (cnt == cnt1) break;
				totalDay1++;
			}
			temp = totalDay2 % 7; // 7로 나눴을때 나머지 구하기 (그 달의 첫번째 요일)
			totalDay2++;
			if (temp == 6 && temp > leave2)
				leave2 = leave2 + temp + 1;
			else if (temp > leave2)
				leave2 = leave2 + 7;
			a = MonthDay[month2] + temp;
			if (month2 == 2 && (year2 % 4 == 0 && (year2 % 100 != 0 || year2 % 400 == 0)))
				a++;
			for (int i = temp; i < a; i++) {
				if (i == leave2) {
					leave2 = leave2 + 7;
					cntt++;
				}
				if (cntt == cnt2) break;
				totalDay2++;
			}
			if (cnt != cnt1 || cntt != cnt2)
				output_fp << "-1" << endl;
			else {
				if (totalDay1 > totalDay2)
					total = totalDay1 - totalDay2;
				else
					total = totalDay2 - totalDay1;
				output_fp << total << endl;
			}	
		}
	}
	input_fp.close();
	output_fp.close();
}