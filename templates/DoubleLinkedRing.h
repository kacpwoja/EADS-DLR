/********************
**Kacper Wojakowski**
***kwojakow 293064***
********************/
#ifndef DOUBLELINKEDRING
#define DOUBLELINKEDRING

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
		~Node();
		Node( const NodeKey &newKey, const NodeInfo &newInfo ): key( newKey ), info( newInfo ), next( nullptr ), previous( nullptr ) {};
	};
	//
	Node<Key, Info> *any;
	
public:
	/******************************
	*        Iterator Class       *
	******************************/
	template <typename IteKey, typename IteInfo>
	class Iterator
	{
		friend class DoubleLinkedRing<IteKey, IteInfo>;
		Node<IteKey, IteInfo> *current;
		struct Content
		{
			IteKey key;
			IteInfo info;
		};
		
	public:
		/**************************************************
		*  Constructors, destructor, copy and assignment  *
		**************************************************/
		Iterator(): current( nullptr ) {};
		Iterator( const Iterator<IteKey, IteInfo> &source );
		Iterator( const Node<IteKey, IteInfo> *source );
		~Iterator();
		Iterator<IteKey, IteInfo>& operator=( const Iterator<IteKey, IteInfo> &rhs );
		
		/**************************************************
		*             Movement Operators                  *
		**************************************************/
		Iterator<IteKey, IteInfo>& operator++();
		Iterator<IteKey, IteInfo> operator++( int );
		Iterator<IteKey, IteInfo>& operator--();
		Iterator<IteKey, IteInfo> operator--( int );
		Iterator<IteKey, IteInfo> operator+( int rhs );
		Iterator<IteKey, IteInfo> operator-( int rhs );
		
		/**************************************************
		*              Access operators                   *
		**************************************************/
		Info& getInfo();
		const Info& getInfo() const;
		Key& getKey();
		const Key& getKey() const;
		Content& operator*();
		const Content& operator*() const;
		Content* operator->();
		const Content* operator->() const;
		
		/**************************************************
		*               Logical operators                 *
		**************************************************/
		bool operator==( const Iterator<IteKey, IteInfo> &rhs ) const;
		bool operator!=( const Iterator<IteKey, IteInfo> &rhs ) const;
		
	};
	//Defining the Constant Iterator
	typedef const Iterator ConstIterator;
	
	/**************************************************
	*  Constructors, destructor, copy and assignment  *
	**************************************************/
	DoubleLinkedRing();
	~DoubleLinkedRing();
	DoubleLinkedRing( const DoubleLinkedRing<Key, Info> &source );
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

	bool operator!=( DoubleLinkedRing<Key, Info> &rhs ) const;
	
	/**************************************************
	*                Iterator Methods                 *
	**************************************************/

	//Returns an Iterator to the "first" element
	//Parameters:	none
	//Returns:		Iterator pointing to any
	Iterator<Key, Info> begin() const;

	//Searches for a Key in the Ring
	//Parameters:	Key to search for
	//Returns:		Iterator pointing to the given Key,
	//				or nullptr if not found
	Iterator<Key, Info> find( const Key &key ) const;
	
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
	void insertAfter( const Key &newKey, const Info &newInfo, const Iterator<Key, Info> &location );

	//Inserts a new element after a specified Key
	//Parameters:	Key and Info of the new element, Key after which to insert and
	//				int denoting the exact occurence of specified key (defaults to 1)
	//Returns:		void
	void insertAfter( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	//Inserts a new element before a specified Iterator
	//Parameters:	Key and Info of the new element, Iterator before which to insert
	//Returns:		void
	void insertBefore( const Key &newKey, const Info &newInfo, const Iterator<Key, Info> &location );

	//Inserts a new element before a specified Key
	//Parameters:	Key and Info of the new element, Key before which to insert and
	//				int denoting the exact occurence of specified key (defaults to 1)
	//Returns:		void
	void insertBefore( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	//Removes an element from the Ring
	//Parameters:	Iterator pointing to the element to be removed
	//Returns:		void
	void remove( const Iterator<Key, Info> &location );

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
#endif
