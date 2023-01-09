#pragma once
#include <iostream>
using namespace std;
class Date{

	// ��Ԫ����
	friend ostream& operator<<(ostream& out, const Date& d);

public:
	// ��ȡĳ��ĳ�µ�����
	int GetMonthDay(int year, int month) const;

	// ȫȱʡ�Ĺ��캯��
	Date(int year = 1, int month = 1, int day = 1);

	// ��ֵ���������
	Date& operator=(const Date& d);

	// �������캯��
	Date(const Date& d);

	// ����+=����
	Date& operator+=(int day);

	// ����+����
	Date operator+(int day) const;

	// ����-����
	Date operator-(int day) const;

	// ����-=����
	Date& operator-=(int day);

	// ǰ��++
	Date& operator++();

	// ����++
	Date operator++(int);

	// ����--
	Date operator--(int);

	// ǰ��--
	Date& operator--();

	// >���������
	bool operator>(const Date& d) const;

	// ==���������
	bool operator==(const Date& d) const;

	// >=���������
	bool operator>=(const Date& d) const;

	// <���������
	bool operator<(const Date& d) const;

	// <=���������
	bool operator<=(const Date& d) const;

	// !=���������
	bool operator!=(const Date& d) const;

	// ����-���� ��������
	int operator-(const Date& d) const;

	// ��ӡ�����ڼ�
	void PrintWeekDay() const;

private:
	int _year;
	int _month;
	int _day;
};

ostream& operator<<(ostream& out, const Date& d);