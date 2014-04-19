#ifndef Iterator_hpp
#define Iterator_hpp

class Iterator
{
public:
	virtual bool hasNext() = 0;		// Tells whether Iterator currently points towards an element of the List
	virtual void *next() = 0;		// Returns current element and steps to the next one
	virtual void remove() = 0;		// Removes element that was most recently returned by next()
}; 

#endif
