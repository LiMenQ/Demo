#include "Date.h"

ostream& operator<<(ostream& out, const Date& d) {
	out << d._year << "/" << d._month << "/" << d._day;
	return out;
}

Date::Date(int year, int month, int day) {
	_year = year;
	_month = month;
	_day = day;
	if (year <= 0 || month <= 0 || month >= 13 || day <= 0 || day >= GetMonthDay(year, month))
		cout << "非法日期" << endl;
}

int Date::GetMonthDay(int year, int month) const {
	static int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (month != 2) 
		return days[month];

	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
		return days[2] + 1;

	return days[2];
}

Date& Date::operator=(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
	return *this;
}

Date::Date(const Date& d) {
	_year = d._year;
	_month = d._month;
	_day = d._day;
}

Date& Date::operator+=(int day) {
	if (day < 0) return *this -= -day;
	_day += day;
	while (_day > GetMonthDay(_year, _month)) {
		_day -= GetMonthDay(_year, _month);
		_month++;
		if (_month == 13) {
			_month = 1;
			_year++;
		}
	}
	return *this;
}

Date Date::operator+(int day) const {
	Date d(*this);
	d += day;
	return d;
}

Date Date::operator-(int day) const {
	Date d(*this);
	d -= day;
	return d;
}

Date& Date::operator-=(int day) {
	if (day < 0) return *this += -day;
	_day -= day;
	while (_day <= 0) {
		_month--;
		if (_month == 0) {
			_month = 12;
			_year--;
		}
		_day += GetMonthDay(_year, _month);
	}

	return *this;
}

Date& Date::operator++() {
	*this += 1;
	return *this;
}

Date Date::operator++(int) {
	Date d(*this);
	*this += 1;
	return d;
}

Date Date::operator--(int) {
	Date d(*this);
	*this -= 1;
	return d;
}

Date& Date::operator--() {
	*this -= 1;
	return *this;
}

bool Date::operator>(const Date& d) const {
	if (_year > d._year) return true;
	if (_year == d._year && _month > d._month) return true;
	if (_year == d._year && _month > d._month && _day > d._day) return true;
	return false;
}

bool Date::operator==(const Date& d) const {
	if (_year == d._year && _month == d._month && _day == d._day)
		return true;
	return false;
}

bool Date::operator>=(const Date& d) const {
	return *this > d || *this == d;
}

bool Date::operator<(const Date& d) const {
	return !(*this > d) && !(*this == d);
}

bool Date::operator<=(const Date& d) const {
	return !(*this > d);
}

bool Date::operator!=(const Date& d) const {
	return !(*this == d);
}

int Date::operator-(const Date& d) const {
	if (*this < d) return d - *this;
	Date min = d;
	int cnt = 0;
	while (min < *this) {
		min++, cnt++;
	}
	return cnt;
}

void Date::PrintWeekDay() const {
	const char* str[] = { "星期一", "星期二", "星期三", "星期四", "星期五", "星期六", "星期天"};
	Date begin(1900, 1, 1);
	int cnt = *this - begin;
	cout << str[cnt % 7] << endl;
}