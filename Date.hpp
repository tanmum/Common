#ifndef __DATE_HPP__
#define __DATE_HPP__

#include "String.hpp"

class Date
{
private:
	int month;
	int day;
	int year;

	String dateStr;

public:
	enum MONTH
	{
		JANUARY = 1,
		FEBRUARY,
		MARCH,
		APRIL,
		MAY,
		JUNE,
		JULY,
		AUGUST,
		SEPTEMBER,
		OCTOBER,
		NOVEMBER,
		DECEMBER
	};

	Date();
	Date(int month, int day, int year);
	Date(const char *dateStr);					// Format: mm/dd/yyyy
	Date(const Date& dt);

	int getMonth();
	int getDay();
	int getYear();
	const char *getStr();

	void setTo(int month, int day, int year);
	void setTo(const char *dateStr);			// Format: mm/dd/yyyy
	
	operator const char * ();
	Date& operator = (const Date& dt);
	Date& operator = (const char *dateStr);		// Format: mm/dd/yyyy
	int compareTo(const Date& dt);
	bool operator == (const Date& dt);
};

#endif