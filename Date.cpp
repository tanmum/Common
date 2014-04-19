#include "Date.hpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

Date::Date() 
{
	time_t seconds = time(0);
	struct tm *t = localtime(&seconds);

	setTo(t->tm_mon + 1, t->tm_mday, 1900 + t->tm_year);
}

Date::Date(int m, int d, int y)
{
	setTo(m, d, y);
}

Date::Date(const Date& dt)
{
	*this = dt;
}

Date::Date(const char *dateStr)					// Format: mm/dd/yyyy
{
	setTo(dateStr);
}

int Date::getMonth() { return month; }
int Date::getDay() { return day; }
int Date::getYear() { return year; }

const char *Date::getStr()
{
	return dateStr; //.getStr();
}

void Date::setTo(int m, int d, int y)
{
	month = m;
	day = d;
	year = y;

	dateStr.clear();
	dateStr << month << "/" << day << "/" << year;
}

void Date::setTo(const char *dateStr)				// Format: mm/dd/yyyy
{
	if (dateStr)
	{
		int m = strtol(dateStr, 0, 10);

		dateStr = strchr(dateStr, '/');
		if (dateStr && dateStr+1)
		{
			dateStr++;

			int d = strtol(dateStr, 0, 10);

			dateStr = strchr(dateStr, '/');
			if (dateStr && dateStr+1)
			{	
				dateStr++;

				int y = strtol(dateStr, 0, 10);		

				setTo(m, d, y);
			}
		}
	}
}

Date::operator const char * ()
{
	return getStr();
}

Date& Date::operator = (const Date& dt)
{
	month = dt.month;
	day = dt.day;
	year = dt.year;
	return *this;
}

Date& Date::operator = (const char *dateStr)		// Format: mm/dd/yyyy
{
	setTo(dateStr);
	return *this;
}

int Date::compareTo(const Date& dt)
{
	if (year == dt.year)
	{
		if (month == dt.month)
		{
			if (day == dt.day)
				return 0;
			else if (day > dt.day)
				return 1;
			else 
				return -1;
		}
		else if (month > dt.month)
			return 1;
		else
			return -1;
	}
	else if (year > dt.year)
		return 1;
	else
		return -1;
}

bool Date::operator == (const Date& dt)
{
	if (!compareTo(dt))
		return true;
	return false;
}
