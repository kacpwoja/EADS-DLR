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
	}
	//
	Node<Key, Info> *any;
	
public:
	//Iterator Class
	template <typename IteKey, typename IteInfo>
	class Iterator
	{
		Node<IteKey, IteInfo> *current;
		
	public:
		//Constructor, destructor, copy and assignment
		Iterator(): current( nullptr ) {};
		~Iterator();
		Iterator( const Iterator<IteKey, IteInfo> &source );
		Iterator<IteKey, IteInfo>& operator=( const Iterator<IteKey, IteInfo> &rhs );
		
		//Movement operators (increment)
		Iterator<IteKey, IteInfo>& operator++();
		Iterator<IteKey, IteInfo> operator++( int );
		Iterator<IteKey, IteInfo>& operator--();
		Iterator<IteKey, IteInfo> operator--( int );
		
		//
		
		
		//Access operator(s)
		Info info() const;
		Key key() const;
		/*Info*/ operator*() const;
		
		//Logical operators
		bool operator==( const Iterator<IteKey, IteInfo> &rhs ) const;
		bool operator!=( const Iterator<IteKey, IteInfo> &rhs ) const;
		
	}
	
	//Constructor, destructor, copy and assignment
	DoubleLinkedRing();
	~DoubleLinkedRing();
	DoubleLinkedRing( const DoubleLinkedRing<Key, Info> &source );
	DoubleLinkedRing<Key, Info>& operator=( const DoubleLinkedRing<Key, Info> &rhs );
	
	//
	void clear();
	void size() const;
	bool isEmpty() const;
	bool search( const Key &key ) const;
	Info get( const Key &location, int occurence = 1 ) const;
	Info get() const;
	
	//Logical Operators
	bool operator==( DoubleLinkedRing<Key, Info> &rhs ) const;
	bool operator!=( DoubleLinkedRing<Key, Info> &rhs ) const;
	
	//
	Iterator<Key, Info> any() const;
	
	void addAfter( const Key &newKey, const Info &newInfo, const Iterator<Key, Info> &location );
	void addAfter( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	void addBefore( const Key &newKey, const Info &newInfo, const Iterator<Key, Info> &location );
	void addBefore( const Key &newKey, const Info &newInfo, const Key &location, int occurence = 1 );
	
	void remove( const Iterator<Key, Info> &location );
	void remove( const Key &location, int occurence = 1 );
	
	void push( const Key &newKey, const Info &newInfo );
	void pop();
	
	//Printing
	void print( std::ostream &os = std::cout ) const;
	friend std::ostream& operator<<( std::ostream &os, const DoubleLinkedRing<Key, Info> &ring );
	
}
#endif
