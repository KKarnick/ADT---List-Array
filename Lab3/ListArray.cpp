
#include "ListArray.h"

template < typename DataType >
List<DataType>::List ( int maxNumber ){
	maxSize = maxNumber;
	size = 0;         //no items added, so size is 0
	cursor = -1;      //cursor is "before" first item (-1)
	dataItems = new DataType[maxSize];  //declare new array of size maxSize
}

template < typename DataType >
List<DataType>::List(const List& source) {
	maxSize = source.maxSize;
	size = source.size;
	cursor = source.cursor;
	//copy data items to new list
	dataItems = new DataType[maxSize];
	for (int i = 0; i < source.size; i++)
		dataItems[i] = source.dataItems[i];
}
    
template < typename DataType >
List<DataType>& List<DataType>::operator= ( const List& source ){
	clear();  //clear all current items in list (maxSize may be larger)
	if (maxSize < source.maxSize)  //if not enough room, change max size
		dataItems = new DataType[maxSize];
	else {
		for (int i = 0; i < source.size; i++)  //source.size shows up as different array sizes (obviously), so maxSize used here
			dataItems[i] = source.dataItems[i];
		size = source.size;
		cursor = source.cursor;
	}
	return *this;
}

template < typename DataType >
List<DataType>::~List (){
	delete[]dataItems;
}

template < typename DataType >
void List<DataType>::insert ( const DataType& newDataItem )
	throw ( logic_error ){
	if (isFull())
		throw logic_error("Cannot insert into full list.");
	else {
		if(!isEmpty())  //if the list is not empty, insert new items at the end of the list
			gotoEnd();
		dataItems[cursor + 1] = newDataItem;  
		size++;  //increment size
		cursor++;   //increment cursor location
	}
}

template < typename DataType >
void List<DataType>::remove () throw ( logic_error ){
	if (isEmpty())
		throw logic_error("Empty list.");
	else {
		for (int i = cursor; i < size - 1; i++)
			dataItems[i] = dataItems[i + 1];  //move all items down one index
		size--;  //marks last item to be able to be written over
		//cursor only need be changed if list now empty or last item deleted
		if (isEmpty())  // if list now empty, cursor points to -1
			cursor = -1;
		else if (cursor == size)   //if last item was removed, cursor updated to point to "new" last item
			cursor = size - 1;
	}
}

template < typename DataType >
void List<DataType>::replace ( const DataType& newDataItem )
	throw ( logic_error ){
	if (isEmpty() )
		throw logic_error("List is empty.");
	else {
		dataItems[cursor] = newDataItem;
	}
}

template < typename DataType >
void List<DataType>::clear (){
	size = 0;  //makes all items irrelevant
	cursor = -1;
}

template < typename DataType >
bool List<DataType>::isEmpty () const{
	if (size == 0)
		return true;
	else
		return false;
}

template < typename DataType >
bool List<DataType>::isFull () const{
	if (size == maxSize)
		return true;
	else
		return false;
}

template < typename DataType >
void List<DataType>::gotoBeginning ()
        throw ( logic_error ){
	if (isEmpty())   //cannot go to beginning of empty list
		throw logic_error("Empty list.");
	else
		cursor = 0;  //set cursor to first index
}

template < typename DataType >
void List<DataType>::gotoEnd ()
        throw ( logic_error ){
	if (isEmpty())  //cannot go to end of empty list
		throw logic_error("Empty list.");
	else 
		cursor = size - 1;  //set cursor to last index used
}

template < typename DataType >
bool List<DataType>::gotoNext ()
        throw ( logic_error ){
	if (isEmpty())  //size - 1 is last index
		throw logic_error("Empty list.");
	else {
		if (cursor == (size - 1))  //cursor in last position; return false (cannot move within bounds)
			return false;
		else {
			cursor = cursor + 1;  //move cursor to next position and return true
			return true;
		}
	}
}

template < typename DataType >
bool List<DataType>::gotoPrior ()
        throw ( logic_error ){
	if (isEmpty() )
		throw logic_error("Empty list.");
	else if (cursor != 0) {
		cursor = cursor - 1;
		return true;
	}
	else
		return false;
}

template < typename DataType >
DataType List<DataType>::getCursor () const
        throw ( logic_error ){
	if (isEmpty() )
		throw logic_error("Empty list.");
	else { 
		return dataItems[cursor];
	}
}

#include "show3.cpp"

template < typename DataType >
void List<DataType>::moveToNth ( int n )
        throw ( logic_error ){
	//takes item at cursor and moves it to location n, shifting all items after
	if (isEmpty())
		throw logic_error("Empty list.");
	else if (n < 0 || n >(size - 1))
		throw logic_error("Out of bounds.");
	else {
		DataType temp = dataItems[cursor];  //set a temp equal to "this" calling item
		for (int i = (size - 1); i > n; i--)
			dataItems[i] = dataItems[i - 1];  //shift all other items past index n
		//place the original calling item in index n		
		dataItems[n] = temp;
	}
}

template < typename DataType >
bool List<DataType>::find ( const DataType& searchDataItem )
        throw ( logic_error ){
	if (isEmpty())
		throw logic_error("Empty list.  Item not located in list.");
	else {
		for (int i = 0; i < size; i++) {
			if (dataItems[i] == searchDataItem)
				return true;
		}
		return false;
	}
}