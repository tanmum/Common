#ifndef List_hpp
#define List_hpp

#include "Iterator.hpp"

class Link;

class List
{
private:
	class Link							// Inner Class
	{
	private:
		void *item;				        // The item I hold
		Link *next;				        // The link I preceed
		Link *prev;				        // The link I succeed

	public:
		Link(void *ob, Link *p);		// Constructor
		~Link();						// Destructor
		Link *append(void *ob);			// I can't hold it since I already hold an item
		void *getItem();			    // Get the item I hold
		Link *getNextLink();		    // Get the Link who's next to me
		Link *getPrevLink();		    // Get the Link who's before to me
		void setNextLink(Link *);		// Set next link
		void setPrevLink(Link *);		// Set nrevious Link
	};

	Link *start;					// The Link that starts the list
	Link *last;						// The last Link of the list

	class ListIterator : public Iterator   // This is an inner class
	{
	private:
        List *list;					// The list I traverse
		Link *current;				// The current Link
		Link *lastRet;				// Link to the item last returned by the List
	public:
		ListIterator(List& l);		// ListIterator Constructor
		ListIterator(ListIterator&);// ListIterator Copy Constructor
		~ListIterator();			// Destructor
		bool hasNext();				// Tells whether Iterator currently points towards an element of the List
		void *next();				// Returns current element and steps to the next one
		void remove();				// Removes the most recent element that was returned by next()
	};

public:
    List();							// List Constructor
    List(List&);					// Copy constructor
	virtual ~List();				// Deallocate all the dynamic objects I've created
	Iterator *getIterator();		// Provide a (temporary) Iterator to myself to the outside world
	void append(void *item);        // Append an item
	void append(List& sl);			// Append all items contained by another List
	int count();					// Count how many items I'm holding
	void remove(void *item);		// Remove an item, if found in the List
	bool contains(void *item);		// Return true if item is in the List
	void *operator[](int i);		// [] Operator (not the most efficient on List)
};

#endif
