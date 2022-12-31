
#ifndef UPDATE_H
#define UPDATE_H
#include <string>
using namespace std;

class upDate
{
private:
	int* p;
	static int numDates;
	string monthNames[12]{ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	string dayNames[7]{ "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
public:
	upDate(); //default constructor
	upDate(int M, int D, int Y); //overloaded constructor
	upDate(int J); //overloaded constructor 
	upDate(const upDate& upDate); //copy constructor
	~upDate(); // destructor

	void setDate(int M, int D, int Y);
	int getMonth() const; 
	int getDay() const; 
	int getYear() const; 
	int dayOfYear() const;
	string getMonthName() const; 
	int julian() const;
	static int GetDateCount();

	upDate& operator= (const upDate& upDate);
	upDate& operator+= (const int& days);
	upDate& operator-= (const int& days);
	upDate& operator++();
	upDate operator++(int);
	upDate& operator--();
	upDate operator--(int);

	friend bool operator==(const upDate& j1, const upDate& j2);
	friend bool operator>(const upDate& j1, const upDate& j2);
	friend bool operator<(const upDate& j1, const upDate& j2);
	friend ostream& operator<<(ostream& output, const upDate& d);
};

upDate operator+ (int l, const upDate& r);
upDate operator+ (const upDate l, const int& r);
upDate operator+ (const upDate l, const upDate& r);
upDate operator- (const upDate l, const int& r);
int operator- (const upDate l, const upDate& r);

#endif
