/********************
**Kacper Wojakowski**
***kwojakow 293064***
********************/
#pragma once

#include <iostream>
#include <new>

template <typename Key, typename Info>
class DoubleLinkedRing
{
	//Node structure
	template <typename NodeKey, typename NodeInfo>
	struct Node
	{
		NodeKey key;
		NodeInfo info;
		Node<NodeKey, NodeInfo> *next;
		Node<NodeKey, NodeInfo> *previous;
		
		Node(): key(), info(), next( nullptr ), previous( nullptr ) {};
		~Node() = default;
		Node( const NodeKey &newKey, const NodeInfo &newInfo ): key( newKey ), info( newInfo ), next( nullptr ), previous( nullptr ) {};
	};
	//
	Node<Key, Info> *any;
	
public:
	class Iterator;
	typedef const Iterator ConstIterator;
	
	/**************************************************
	*  Constructors, destructor, copy and assignment  *
	**************************************************/
	DoubleLinkedRing(): head( nullptr ) {};
	~DoubleLinkedRing() { clear(); };
	DoubleLinkedRing( const DoubleLinkedRing<Key, Info> &source ) { *this = source; };
	DoubleLinkedRing<Key, Info>& operator=( const DoubleLinkedRing<Key, Info> &rhs );
	
	/**************************************************
	*                General Methods                  *
	**************************************************/

	//Clears the Ring
	//Parameters:	None
	//Returns:		void
	void clear();
	
	//Counts the number of elements in the Ring
	//Parameters:	none
	//Returns:		number of elements in the Ring
	int size() const;

	//Checks if the ring is empty
	//Parameters:	none
	//Returns:		true if empty, false otherwise
	bool isEmpty() const;

	//Checks if a given Key is in the Ring
	//Parameters:	Key to search for
	//Returns:		true if exists, false otherwise
	bool search( const Key &key ) const;
	
	/**************************************************
	*               Logical Operators                 *
	**************************************************/

	bool operator==( DoubleLinkedRing<Key, Info> &rhs ) const;

	bool operator!=( DoubleLinkedRing<Key, Info> &rhs ) const { return !( *this == rhs ); };
	
	/**************************************************
	*                Iterator Methods                 *
	**************************************************/

	//Returns an Iterator to the "first" element
	//Parameters:	none
	//Returns:		Iterator pointing to any
	Iterator begin() const { return Iterator( any ); };

	//Searches for a Key in the Ring
	//Parameters:	Key to search for
	//Returns:		Iterator pointing to the given Key,
	//				or nullptr if not found
	Iterator find( const Key &key, int occurence = 1 ) const;
	
	/**************************************************
	*              Inserting and Removing             *
	**************************************************/

	//Adds a new element at the back of the Ring (before any)
	//Parameters:	Key and Info of the new element
	//Returns:		void
	void push( const Key &newKey, const Info &newInfo );

	//Inserts a new element after a specified Iterator
	//Parameters:	Key and Info of the new element, Iterator after which to insert
	//Returns:		void
	void insertAfter( const Key &newKey, const Info &newInfo, const Iterator &location );

	//Inserts a new element after a specified Key
	//Parameters:	Key and Info of the new element, Key after which to insert and
	//				int denoting the exact occurence of specified key (defaults to 1)
	//Returns:		void
	void insertAfter( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	//Inserts a new element before a specified Iterator
	//Parameters:	Key and Info of the new element, Iterator before which to insert
	//Returns:		void
	void insertBefore( const Key &newKey, const Info &newInfo, const Iterator &location );

	//Inserts a new element before a specified Key
	//Parameters:	Key and Info of the new element, Key before which to insert and
	//				int denoting the exact occurence of specified key (defaults to 1)
	//Returns:		void
	void insertBefore( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	//Removes an element from the Ring
	//Parameters:	Iterator pointing to the element to be removed
	//Returns:		void
	void remove( const Iterator &location );

	//Removes an element from the Ring
	//Parameters:	Key to be removed and its exact occurence (defaults to 1)
	//Returns:		void
	void remove( const Key &location, int occurence = 1 );
	
	/**************************************************
	*                    Printing                     *
	**************************************************/

	//Prints the list into a stream
	//Parameters:	an std::ostream to be printed to, defaults to std::cout
	//Returns:		void
	void print( std::ostream &os = std::cout ) const;

	friend std::ostream& operator<<( std::ostream &os, const DoubleLinkedRing<Key, Info> &ring );
	
};

template<typename Key, typename Info>
inline DoubleLinkedRing<Key, Info>& DoubleLinkedRing<Key, Info>::operator=( const DoubleLinkedRing<Key, Info>& rhs )
{
	if( this == &rhs )
		return *this;

	clear();
	
	if( rhs.isEmpty() )
		return *this;

	auto current = rhs.any;
	do
	{
		push( current->key, current->info );
	} while( current != any );

	return *this;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::clear()
{
	while( any != nullptr )
	{
		auto temp = any;
		any = any->next;
		temp->next->previous = temp->previous;
		temp->previous->next = temp->next;
		delete temp;
	}
}

template<typename Key, typename Info>
int DoubleLinkedRing<Key, Info>::size() const
{
	if( any == nullptr )
		return 0;

	int output = 0;
	auto current = any;

	do
	{
		output++;
		current = current->next;
	} while( current != any );

	return output;
}

template<typename Key, typename Info>
bool DoubleLinkedRing<Key, Info>::isEmpty() const
{
	return any == nullptr;
}

template<typename Key, typename Info>
bool DoubleLinkedRing<Key, Info>::search( const Key & key ) const
{
	if( any == nullptr )
		return false;

	auto current = any;
	do
	{
		if( current->key == key )
			return true;
		current = current->next;
	} while( current != any );
	return false;
}

template<typename Key, typename Info>
bool DoubleLinkedRing<Key, Info>::operator==( DoubleLinkedRing<Key, Info>& rhs ) const
{
	if( size() != rhs.size() )
		return false;

	if( isEmpty() )
		return true;

	auto curr = any;
	auto rhcurr = rhs.any;
	return false;
}

template<typename Key, typename Info>
DoubleLinkedRing<Key,Info>::Iterator DoubleLinkedRing<Key, Info>::find( const Key & key, int occurence ) const
{
	if( any == nullptr )
		return Iterator();

	int o = 0;
	auto current = any;
	do
	{
		if( current->key == key && ++o = occurence; )
			return Iterator( current );
		current = current->next;
	} while( current != any );

	return Iterator();
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::push( const Key & newKey, const Info & newInfo )
{
	auto newNode = new Node( newKey, newInfo );

	if( any == nullptr )
	{
		any = newNode;
		return;
	}

	newNode->next = any;
	newNode->previous = any->previous;

	any->previous->next = newNode;
	any->previous = newNode;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::insertAfter( const Key & newKey, const Info & newInfo, const Iterator & location )
{
	if( location.current == nullptr )
		return;

	auto insert = new Node( newKey, newInfo );
	insert->previous = location.current;
	insert->next = location.current->next;
	location.current->next->previous = insert;
	location.current->next = insert;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::insertAfter( const Key & newKey, const Info & newInfo, const Key & location, int occurence )
{
	auto iter = find( location, occurence );
	insertAfter( newKey, newInfo, iter );
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::insertBefore( const Key & newKey, const Info & newInfo, const Iterator & location )
{
	if( location.current == nullptr )
		return;

	auto insert = new Node( newKey, newInfo );
	insert->next = location.current;
	insert->previous = location.current->previous;
	location.current->previous->next = insert;
	location.current->previous = insert;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::insertBefore( const Key & newKey, const Info & newInfo, const Key & location, int occurence )
{
	auto iter = find( location, occurence );
	insertBefore( newKey, newInfo, iter );
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::remove( const Iterator & location )
{
	if( location.current == nullptr )
		return;

	location.current->next->previous = location.current->previous;
	location.current->previous->next = location.current->next;
	delete location.current;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::remove( const Key & location, int occurence )
{
}
