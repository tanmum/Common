// String.cpp

#include "String.hpp"

String::String(const char *str)
{
	s = 0;								// Always initialize
	length = 0;
	initCopy(str);
}
    
String::String(const String& string)
{
	s = 0;								
	length = 0;
	initCopy(string.s);
}
    
String::String(const String *st)
{
	s = 0;								
	length = 0;
	if (st && st->s)
		initCopy(st->s);
}
    
String::String(long length)
{
	s = 0;
	String::length = 0; 

	if (length > 0)
		create(length);
}    
    
String::~String()
{
	if (s)
	{
		delete[] s;						// Deleting an array
		s = 0, length = 0;
	}
}

void String::initCopy(const char *str)
{
	if (str)
	{
		create(strLen(str));
		copy(str);
	}
}

void String::clear()
{
	if (s)
		for (long i = 0; i < length; i++)
			s[i] = 0;
}

       
long String::ln()const
{
	long l = 0;
	if (s)
		while (s[l]) 
			l++;
	return l;
}       
       
void String::stncpy(char *dest, const char *src, long n)
{
	if (dest && src)
		while ((n-- > 0) && (*dest++ = *src++))
			;
}
  
void String::copy(const char *str)
{
	if (s && str)
		stncpy(s, str, length - 1);
}

long String::max(long l, long m) const
{
	return (l >= m) ? l : m;
}

void String::create(long l)
{
	length = max(l+1, 2*length);	// avoid too frequent re-allocations
	s = new char[length];
	clear();
}

void String::prt(FILE *f) const
{
	if (s)
		fprintf(f, "<%s>\n", s);
	else
		fprintf(f, "<>\n");
} 

long String::strLen(const char *t) const
{
	long ret = 0;

	if (t)
		while (*t++)
			ret++;

	return ret;
}

void String::setTo(const char *t)
{
	if (t)
	{
		long l = strLen(t);  			// length needed
		l = (l >= 1 ? l : 1);			// consider it's at least equal to 1
		if (l > length - 1)				// allocate more space if needed
		{
			if (s) delete [] s, s = 0, length = 0;
			create(l);
		}
		copy(t);						// copy contents t is pointing to
	}
	else
		clear();
}


String& String::operator = (const char *t)
{
	if (t)
		setTo(t);

	return *this;				
}

String& String::operator = (const String& str)
{
	(*this) = str.s;			// Let's re-use our existing code!
	return *this;
}
  
String& String::operator = (char c)
{            
	static char tmp[2];

	tmp[0] = c;
	tmp[1] = 0;

	(*this) = tmp;

	return *this;
}

String& String::operator << (const char *t)
{
	if (t)
		if (!s)								// If I'm empty
			(*this) = t;					// ... just copy
		else
		{
			long leftLength = strLen(s);
			long rightLength = strLen(t);
			long newLength = leftLength + rightLength;
			if (newLength> length - 1)
			{
				String tmp(s);						// Copy old string
				delete[] s, s = 0, length = 0;		// De-allocate old segment
				create(newLength);					// Allocate enough memory & clear
				copy(tmp.s);						// Put old string back
			}
			stncpy(s + leftLength, t, rightLength);	// Append to the end
		}

	return *this;
}



String& String::operator << (char c)
{
	static char tmp[2];

	tmp[0] = c;
	tmp[1] = 0;

	(*this) << tmp;

	return *this;
} 
 
String& String::operator << (const String &str)
{
	(*this) << str.s;
	return *this;
}  

String& String::operator << (float number)
{
    (*this) << (double) number;

	return *this;
}

String& String::operator << (double number)
{
    String tmp(400);
    
    sprintf(tmp.s, "%f", number); // DevCPP doesn't take sprintf_s
    (*this) << tmp;

	return *this;
}


String& String::operator << (int number)
{
    String tmp(400);
    
    sprintf(tmp.s, "%d", number); // DevCPP doesn't take sprintf_s
    (*this) << tmp;

	return *this;
}

bool String::operator == (const String& str) const
{
	bool same = false;
	char *l = s, *r = str.s;

	if (l && r)
		while ((same = (*l == *r++)) && *l++);

	return same;
}

bool String::operator != (const String& str) const
{
	return !((*this) == str);
}

bool String::operator == (const char *cp) const
{
	return (*this) == String(cp);
}


String String::operator + (const String& str)const
{
	String plus(s);
	plus << str;
	return plus;
}

