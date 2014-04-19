#include "List.hpp"
#include <iostream>
using namespace std;

List::Link::Link(void *ob, Link *p)
{
	item = ob;							// The item I hold is set here
	prev = p;
	next = 0;
}

List::Link::~Link()
{
	if (next) delete next, next = 0;
	prev = 0;
	item = 0;
}


List::Link *List::Link::append(void *ob)			// I can't hold it since I already hold an item
{
	next = new Link(ob, this);			// ...let's create a Link that will hold the item
	return next;
}

void *List::Link::getItem()					// Get the item I hold
{
	return item;
}

List::Link *List::Link::getNextLink()				// Get the Link who's next to me
{
	return next;
}

void List::Link::setNextLink(Link *n)
{
	next = n;
}

List::Link *List::Link::getPrevLink()				// Get the Link who's before to me
{
	return prev;
}

void List::Link::setPrevLink(Link *p)
{
	prev = p;
}

List::List()
{
    start = 0;
    last = 0;
}

List::List(List &l)
{
    start = 0;
    last = 0;

	for (Link *cursor = l.start; cursor; cursor = cursor->getNextLink())
		append(cursor->getItem());
}

List::~List()
{
	if (start) delete start, start = 0;		// Deallocate all Links
	last = 0;								// last is not used anymore
	
	/*
	for (Link *prev = 0; last; last = prev)	// Alternate deallocation 
	{
		prev = last->getPrevLink();
		delete last;
	}
	start = 0;
	*/
}

Iterator *List::getIterator()
{
	return new ListIterator(*this);
}

void List::append(void *item)				// Append an item
{
	if (!start)								// If I don't have a Link...
		last = start = new Link(item, 0);   // ... then it's the first item
	else									// Otherwise...
		last = last->append(item);			// ... append at the end
}

void List::append(List& sl)					// Append items contained in a List
{
	Iterator *it= sl.getIterator();

	while (it->hasNext())
		append(it->next());

	delete it, it = 0;
}

int List::count()
{
	int cnt = 0;

	for (ListIterator it(*this); it.hasNext(); it.next())	// This is a private and automatic iterator variable
		cnt++;

	return cnt;
}

void List::remove(void *item)
{
	for (ListIterator iterator(*this); iterator.hasNext(); )	// This is a private and automatic iterator variable
		if (item == iterator.next())							// If item found in List...
			iterator.remove();									// ...have the Iterator remove it
}

bool List::contains(void *item)
{
	bool found = false;

	for (Link *cursor = start; cursor && !found; cursor = cursor->getNextLink())
		found = (cursor->getItem() == item);

	return found;
}

List::ListIterator::ListIterator(List& l)	// ListIterator constructor
{
	list = &l;								// Know thy list
	current = l.start;						// Always start with the first item
	lastRet = 0;							// Nothing has ever been returned yet
}

List::ListIterator::ListIterator(ListIterator& li)	// ListIterator copy constructor
{
	list = li.list;								
	current = li.current;						
	lastRet = li.lastRet;
}

List::ListIterator::~ListIterator()
{
	//cout << "ListIterator::~ListIterator()\n\n";
}

bool List::ListIterator::hasNext()
{
	return current != 0;					// If there is a Link, there is an element
}

void *List::ListIterator::next()
{
	void *object = 0;

	lastRet = current;							// This is the Link for the object we're about to return

	if (current)
		current = current->getNextLink();		// Iteration happens here: get to next Link
	
	if (lastRet)
		object = lastRet->getItem();			// Here is the element we had been holding (null or not...)			

	return object; 
}

void List::ListIterator::remove()				// Removes the most recent element (lastRet) that was returned by next()
{
	if (lastRet && list)						// Pass if last item returned was null or there is no list
	{
		Link *before = lastRet->getPrevLink();	// Link before item to remove
		Link *after = lastRet->getNextLink();	// Link after item to remove

		if (before)
			before->setNextLink(after);			// Link before should now point to Link after
		else									// That was first item in list
			list->start = after;				// List's "start" item is now the one after

		if (after)
			after->setPrevLink(before);			// Link after should now point to Link before
		else									// That was the last item in List
			list->last = before;				// List's "last" item is now the one before


		lastRet->setNextLink(0);				// This Link is isolated now.
		lastRet->setPrevLink(0);				// This Link is isolated now.
		delete lastRet, lastRet = 0;			// Get rid of item that was last returned and reset lastRet
	}
}

void *List::operator[](int i)					// Simple [] operator. Can never be efficient with a linked list...
{
	void *ret = 0;

	Link *link = start;

	if (i >= 0 && link)
		for (int j = 0; j <= i && link; j++)
			if (link)
			{
				if (j == i)
					ret = link->getItem();		// Get the item at the requested index
				link = link->getNextLink();		// Get to next link
			}

	return ret;
}
