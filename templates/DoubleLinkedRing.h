/********************
**Kacper Wojakowski**
***kwojakow 293064***
********************/
#pragma once

#include <iostream>
#include <new>
#include <memory>

template <typename Key, typename Info>
class DoubleLinkedRing
{
	//Node structure
	struct Node
	{
		Key key;
		Info info;
		Node *next;
		Node *previous;
		
		Node(): key(), info(), next( nullptr ), previous( nullptr ) {};
		~Node() = default;
		Node( const Key &newKey, const Info &newInfo ): key( newKey ), info( newInfo ), next( nullptr ), previous( nullptr ) {};
	};
	//
	Node *any;
	
public:
	/******************************
	*        Iterator Class       *
	******************************/
	class Iterator
	{
		friend class DoubleLinkedRing;
		mutable Node *current;
	public:
		struct Content
		{
			Key& key;
			Info& info;
		};
		/**************************************************
		*  Constructors, destructor, copy and assignment  *
		**************************************************/
		Iterator(): current( nullptr ) {};
		Iterator( const Iterator &source ): current( source.current ) {};
		Iterator( Node *source ): current( source ) {};
		~Iterator() = default;
		Iterator& operator=( const Iterator &rhs )
		{
			current = rhs.current;
			return *this;
		};

		/**************************************************
		*             Movement Operators                  *
		**************************************************/
		Iterator& operator++() const
		{
			current = current->next;
			return *this;
		};

		Iterator operator++( int ) const
		{
			Iterator temp( *this );
			current = current->next;
			return temp;
		};

		Iterator& operator--() const
		{
			current = current->previous;
			return *this;
		};

		Iterator operator--( int ) const
		{
			Iterator temp( *this );
			current = current->previous;
			return temp;
		};

		Iterator operator+( int rhs ) const
		{
			Iterator temp( *this );
			for( int i = 0; i < rhs; i++ )
				temp.current = temp.current->next;
			return temp;
		};

		Iterator operator-( int rhs ) const
		{
			Iterator temp( *this );
			for( int i = 0; i < rhs; i++ )
				temp.current = temp.current->previous;
			return temp;
		};

		/**************************************************
		*              Access operators                   *
		**************************************************/
		Info& getInfo() {	return current->info; };
		const Info& getInfo() const { return current->info; };
		Key& getKey() { return current->key; };
		const Key& getKey() const { return current->key; };

		Content operator*()
		{
			Content output{ current->key, current->info };
			return output;
		};

		const Content operator*() const
		{
			Content output{ current->key, current->info };
			return output;
		};

		Content* operator->()
		{
			std::unique_ptr<Content> output( new Content{ current->key, current->info } );
			return output.get();
		};

		const Content* operator->() const
		{
			std::unique_ptr<Content> output( new Content{ current->key, current->info } );
			return &output;
		};;

		/**************************************************
		*               Logical operators                 *
		**************************************************/
		bool operator==( const Iterator &rhs ) const { return current == rhs.current; };
		bool operator!=( const Iterator &rhs ) const { return current != rhs.current; };

	};
	typedef const Iterator ConstIterator;
	
	/**************************************************
	*  Constructors, destructor, copy and assignment  *
	**************************************************/
	DoubleLinkedRing(): any( nullptr ) {};
	~DoubleLinkedRing() { clear(); };
	DoubleLinkedRing( const DoubleLinkedRing<Key, Info> &source ): any( nullptr ) { *this = source; };
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

	friend std::ostream& operator<<( std::ostream &os, const DoubleLinkedRing<Key, Info> &ring ) { ring.print( os ); return os; };
	
};

template<typename Key, typename Info>
inline DoubleLinkedRing<Key, Info>& DoubleLinkedRing<Key, Info>::operator=( const DoubleLinkedRing<Key, Info>& rhs )
{
	if( this == &rhs )
		return *this;

	clear();

	auto current = rhs.any;
	if( current == nullptr )
		return *this;
	do
	{
		push( current->key, current->info );
		current = current->next;
	} while( current != rhs.any );

	return *this;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::clear()
{
	if( any == nullptr )
		return;

	auto curr = any->next;
	do
	{
		auto temp = curr;
		curr = curr->next;
		delete temp;
	} while( curr != any );

	delete any;

	any = nullptr;
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

	if( any == nullptr )
		return true;

	auto left = any;
	auto right = rhs.any;
	do
	{
		if( left->key != right->key || left->info != right->info )
			return false;

		left = left->next;
		right = right->next;
	} while( left != any && right != rhs.any );

	return true;
}

template<typename Key, typename Info>
typename DoubleLinkedRing<Key,Info>::Iterator DoubleLinkedRing<Key, Info>::find( const Key & key, int occurence ) const
{
	if( any == nullptr )
		return Iterator();

	int o = 0;
	auto current = any;
	do
	{
		if( current->key == key && ++o == occurence )
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
		any->next = any;
		any->previous = any;
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
	if( any == any->next )
	{
		delete any;
		any = nullptr;
	}

	location.current->next->previous = location.current->previous;
	location.current->previous->next = location.current->next;
	any = location.current->next;
	delete location.current;
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::remove( const Key & location, int occurence )
{
	auto iter = find( location, occurence );
	remove( iter );
}

template<typename Key, typename Info>
void DoubleLinkedRing<Key, Info>::print( std::ostream & os ) const
{
	if( isEmpty() )
		return;

	auto current = any;
	do
	{
		os << "Key: " << current->key << " Info: " << current->info << std::endl;
		current = current->next;
	} while( current != any );
}
