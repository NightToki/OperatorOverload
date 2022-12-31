#include "upDate.h"
#include <iostream>

int Greg2Julian(int month, int day, int year)
{
	int jul = day - 32075 + 1461 *
		(year + 4800 + (month - 14) / 12) / 4 + 367 *
		(month - 2 - (month - 14) / 12 * 12) /
		12 - 3 * ((year + 4900 + (month - 14) / 12) / 100) / 4;
	return jul;
}

void Julian2Greg(int JD, int* p) {
	int L, N, I, J, K;
	L = JD + 68569;
	N = 4 * L / 146097;
	L = L - (146097 * N + 3) / 4;
	I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	J = 80 * L / 2447;
	K = L - 2447 * J / 80;
	L = J / 11;
	J = J + 2 - 12 * L;
	I = 100 * (N - 49) + I + L;

	p[2] = I;
	p[0] = J;
	p[1] = K;
}

bool isLeapYear(int Y)
{
	if (Greg2Julian(Y, 3, 1) - Greg2Julian(Y, 2, 28) == 2)
	{
		return true;
	}
	return false;
}


upDate::upDate() {
	p = new int[3];
	p[0] = 5;
	p[1] = 11;
	p[2] = 1959;
	numDates++;
}

upDate::upDate(int M, int D, int Y) {
	p = new int[3];
	switch (M)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (D > 31 || D < 1)
		{
			p[0] = 5; p[1] = 11; p[2] = 1959;
		}
		else
		{
			p[0] = M; p[1] = D; p[2] = Y;
		}
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (D > 30 || D < 1)
		{
			p[0] = 5; p[1] = 11; p[2] = 1959;
		}
		else
		{
			p[0] = M; p[1] = D; p[2] = Y;
		}
		break;
	case 2:
		if (isLeapYear(Y))
		{
			if (D > 29 || D < 1)
			{
				p[0] = 5; p[1] = 11; p[2] = 1959;
			}
			else
			{
				p[0] = M; p[1] = D; p[2] = Y;
			}
			break;
		}
		else if (D > 28 || D < 1)
		{
			p[0] = 5; p[1] = 11; p[2] = 1959;
		}
		else
		{
			p[0] = M; p[1] = D; p[2] = Y;
		}
		break;
	default: p[0] = 5; p[1] = 11; p[2] = 1959;
	}
	numDates++;
}

upDate::upDate(int J) {
	p = new int[3];
	Julian2Greg(J, p);
	numDates++;
}

upDate::upDate(const upDate& upDate) {
	p = new int[3];
	for (int i = 0; i < 3; i++)
		p[i] = upDate.p[i];
	numDates++;
}

upDate::~upDate()
{
	delete[] p;
	numDates--;
}

void upDate::setDate(int M, int D, int Y) { 
	p[0] = M;
	p[1] = D;
	p[2] = Y; 
}

int upDate::getMonth() const
{
	return p[0];
}

int upDate::getDay() const
{
	return p[1];
}

int upDate::getYear() const
{
	return p[2];
}

int upDate::dayOfYear() const
{
	int nJ = Greg2Julian(1, 1, this->p[2]);
	int dJ = Greg2Julian(this->p[0], this->p[1], this->p[2]);
	return dJ - nJ + 1;
}

string upDate::getMonthName() const
{
	return monthNames[p[0] - 1];
}

int upDate::julian() const {
	return Greg2Julian(p[0], p[1], p[2]);
}

int upDate::numDates = 0;
int upDate::GetDateCount() {
	return numDates;
}

upDate& upDate::operator= (const upDate& upDate) {
	for (int i = 0; i < 3; i++)
		p[i] = upDate.p[i];
	return *this;
}

upDate& upDate::operator+= (const int& days) {
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	thisJulian += 5;
	Julian2Greg(thisJulian, p);
	return *this;
}

upDate& upDate::operator-= (const int& days) {
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	thisJulian -= 5;
	Julian2Greg(thisJulian, p);
	return *this;
}

upDate& upDate::operator++() {
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	++thisJulian;
	Julian2Greg(thisJulian, p);
	return *this;
}

upDate upDate::operator++(int) {
	upDate temp = *this;
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	++thisJulian;
	Julian2Greg(thisJulian, p);
	return temp;
}

upDate& upDate::operator--() {
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	--thisJulian;
	Julian2Greg(thisJulian, p);
	return *this;
}

upDate upDate::operator--(int) {
	upDate temp = *this;
	int thisJulian = Greg2Julian(p[0], p[1], p[2]);
	--thisJulian;
	Julian2Greg(thisJulian, p);
	return temp;
}

bool operator==(const upDate& j1, const upDate& j2) {
	return (j1.p[0] == j2.p[0] && j1.p[1] == j2.p[1] && j1.p[2] == j2.p[2]);

}

bool operator>(const upDate& j1, const upDate& j2) {
	int jul1 = Greg2Julian(j1.p[0], j1.p[1], j1.p[2]);
	int jul2 = Greg2Julian(j2.p[0], j2.p[1], j2.p[2]);

	if (jul1 > jul2) {
		return true;
	}
	else {
		return false;
	}
}

bool operator<(const upDate& j1, const upDate& j2) {
	int jul1 = Greg2Julian(j1.p[0], j1.p[1], j1.p[2]);
	int jul2 = Greg2Julian(j2.p[0], j2.p[1], j2.p[2]);
	if (jul1 < jul2) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& output, const upDate& d) {
	output << d.p[0] << "/" << d.p[1] << "/" << d.p[2];
	return output;
}

upDate operator+ (int l, const upDate& r) {
	int rJulian = Greg2Julian(r.getMonth(), r.getDay(), r.getYear());
	l += rJulian;
	upDate temp(l);
	return temp;
}

upDate operator+ (const upDate l, const int& r) {
	int lJulian = Greg2Julian(l.getMonth(), l.getDay(), l.getYear());
	lJulian += r;
	upDate temp(lJulian);
	return temp;
}

upDate operator+ (const upDate l, const upDate& r) {
	int lJulian = Greg2Julian(l.getMonth(), l.getDay(), l.getYear());
	int rJulian = Greg2Julian(r.getMonth(), r.getDay(), r.getYear());
	lJulian += rJulian;
	upDate temp(lJulian);
	return temp;
}

upDate operator- (const upDate l, const int& r) {
	int lJulian = Greg2Julian(l.getMonth(), l.getDay(), l.getYear());
	lJulian -= r;
	upDate temp(lJulian);
	return temp;
}

int operator- (const upDate l, const upDate& r) {
	int lJulian = Greg2Julian(l.getMonth(), l.getDay(), l.getYear());
	int rJulian = Greg2Julian(r.getMonth(), r.getDay(), r.getYear());
	return (lJulian - rJulian);
}