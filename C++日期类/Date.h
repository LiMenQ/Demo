#pragma once
#include <iostream>
using namespace std;
class Date{

	// 友元函数
	friend ostream& operator<<(ostream& out, const Date& d);

public:
	// 获取某年某月的天数
	int GetMonthDay(int year, int month) const;

	// 全缺省的构造函数
	Date(int year = 1, int month = 1, int day = 1);

	// 赋值运算符重载
	Date& operator=(const Date& d);

	// 拷贝构造函数
	Date(const Date& d);

	// 日期+=天数
	Date& operator+=(int day);

	// 日期+天数
	Date operator+(int day) const;

	// 日期-天数
	Date operator-(int day) const;

	// 日期-=天数
	Date& operator-=(int day);

	// 前置++
	Date& operator++();

	// 后置++
	Date operator++(int);

	// 后置--
	Date operator--(int);

	// 前置--
	Date& operator--();

	// >运算符重载
	bool operator>(const Date& d) const;

	// ==运算符重载
	bool operator==(const Date& d) const;

	// >=运算符重载
	bool operator>=(const Date& d) const;

	// <运算符重载
	bool operator<(const Date& d) const;

	// <=运算符重载
	bool operator<=(const Date& d) const;

	// !=运算符重载
	bool operator!=(const Date& d) const;

	// 日期-日期 返回天数
	int operator-(const Date& d) const;

	// 打印是星期几
	void PrintWeekDay() const;

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);