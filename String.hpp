// String.hpp

#ifndef STRING_HPP
#define STRING_HPP

#include <stdio.h>

class String						// The FILE data type is defined in stdio.h
{
private:

	long length;					// character string length
	char *s;						// Actual data

	void stncpy(char *dest, const char *src, long n); // Copy n characters of src into dest									
	void initCopy(const char *str);	// Initial Copy of char string	
	void create(long i);			// create a character string of length i
	long strLen(const char *t) const;// Return length of t	
	void copy(const char *str);		// Copy contents of str into local char string
	long max(long l, long m)const;	// returns biggest long

public:
	
	// Note: No default constructor...

	String(const char *str = 0);	// String initialized with a char string	
	String(const String& st);		// String initialized with a String	reference
	String(const String *sp);		// String initialized with a String	pointer
	String(long l);					// String with initial length of l	
	
	~String();						// Destructor to clean up when object is gone

	void prt(FILE *f = stderr)const;// Print out current contents into f, or stderr by default
	long ln()const;					// Return current content's length 
	void clear();					// Clear out entire contents
	void setTo(const char *t);		// Set string to t char String
	const char *getStr()const{return s;};// Get char string

	String& operator = (const char *t);		// Assign t
	String& operator = (const String& str);	// Assign str.s
	String& operator = (char c);		// Assign c

	String& operator << (const char *t);	// Append t at the end
	String& operator << (const String &str);// Append str.s at the end
	String& operator << (char c);			// Append c at the end
	String& operator << (float f);			// Append f at the end
	String& operator << (double f);			// Append f at the end
	String& operator << (int i);			// Append i at the end

	bool operator == (const String& str)const;	// Compare to str
	bool operator != (const String& str)const;	// Compare to str

	bool operator == (const char *cp)const;		// Compare to char *

	String operator + (const String& str)const;	// Returns a temporary String holding concatenation of this String with argument String

	operator const char * () const {return s;}	// Conversion operator to turn a String into a char* 
};

#endif

