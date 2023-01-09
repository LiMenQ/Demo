#include "Date.h"

void test1() {
	Date d(2022, 100, 2);
	cout << d << endl;
	int ret = d.GetMonthDay(2000, 2);
	cout << ret << endl; 
	Date d2(2023, 1, 9);
	d = d2;
	cout << d << endl;
	Date d3(d2);
	cout << d3 << endl;
	d3 += 5000;
	cout << d3 << endl;
	Date d4 = d3 + 1000;
	cout << d4;
}

void test2() {
	Date d1(2023, 1, 9);
	d1 -= 1000;
	Date d2 = d1 - 1000;
	cout << d2 << endl;
	cout << ++d2 << endl;
	cout << d2++ << endl;
	cout << d2-- << endl;
	cout << d2 << endl;
	cout << --d2 << endl;
	cout << d1 << endl;
	cout << d2 << endl;
	cout << (d2 > d1) << endl;
	cout << (d2 < d1) << endl;
	cout << (d2 <= d1) << endl;
	cout << (d2 == d1) << endl;
	cout << (d2 >= d1) << endl;
	cout << (d2 != d1) << endl;
	Date d3(2022, 5, 5);
	Date d4(2024, 4, 28);
	cout << (d3 - d4) << endl;
	Date d5(2023, 4, 28);
	d5.PrintWeekDay();
}

int main() {

	// test1();
	test2();

	return 0;
}