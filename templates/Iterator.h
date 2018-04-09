#pragma once

#include "DoubleLinkedRing.h"

/******************************
*        Iterator Class       *
******************************/
template <typename Key, typename Info>
class DoubleLinkedRing<Key, Info>::Iterator
{
	friend class DoubleLinkedRing<Key, Info>;
	Node<Key, Info> *current;
	struct Content
	{
		Key key;
		Info info;
	};

public:
	/**************************************************
	*  Constructors, destructor, copy and assignment  *
	**************************************************/
	Iterator(): current( nullptr ) {};
	Iterator( const Iterator &source ): current( source.current ) {};
	Iterator( const Node<Key, Info> *source ): current( source ) {};
	~Iterator() = default;
	Iterator& operator=( const Iterator &rhs );

	/**************************************************
	*             Movement Operators                  *
	**************************************************/
	Iterator& operator++() const;
	Iterator operator++( int ) const;
	Iterator& operator--() const;
	Iterator operator--( int ) const;
	Iterator operator+( int rhs ) const;
	Iterator operator-( int rhs ) const;

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
	bool operator==( const Iterator &rhs ) const { return current == rhs.current; };
	bool operator!=( const Iterator &rhs ) const { return current != rhs.current; };

};

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator& DoubleLinkedRing<Key, Info>::Iterator::operator=( const Iterator<Key, Info>& rhs )
{
	current = rhs.current;
	return *this;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info>& DoubleLinkedRing<Key, Info>::Iterator::operator++() const
{
	current = current->next;
	return *this;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info> DoubleLinkedRing<Key, Info>::Iterator::operator++( int ) const
{
	Iterator<Key, Info> temp( *this );
	current = current->next;
	return temp;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info>& DoubleLinkedRing<Key, Info>::Iterator::operator--() const
{
	current = current->previous;
	return *this;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info> DoubleLinkedRing<Key, Info>::Iterator::operator--( int ) const
{
	Iterator<Key, Info> temp;
	current = current->previous;
	return tmep;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info> DoubleLinkedRing<Key, Info>::Iterator::operator+( int rhs ) const
{
	Iterator<Key, Info> temp( *this );
	for( int i = 0; i < rhs; i++ )
		temp.current = temp.current->next;
	return temp;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info> DoubleLinkedRing<Key, Info>::Iterator::operator-( int rhs ) const
{
	Iterator<Key, Info> temp( *this );
	for( int i = 0; i < rhs; i++ )
		temp.current = temp.current->previous;
	return temp;
}

template <typename Key, typename Info>
Info & DoubleLinkedRing<Key, Info>::Iterator::getInfo()
{
	return current->info;
}

template <typename Key, typename Info>
const Info & DoubleLinkedRing<Key, Info>::Iterator::getInfo() const
{
	return current->info;
}

template <typename Key, typename Info>
Key & DoubleLinkedRing<Key, Info>::Iterator::getKey()
{
	return current->key;
}

template <typename Key, typename Info>
const Key & DoubleLinkedRing<Key, Info>::Iterator::getKey() const
{
	return current->key;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info>::Content<Key, Info> & DoubleLinkedRing<Key, Info>::Iterator::operator*()
{
	Content output;
	output.key = current->key;
	output.info = current->info;
	return output;
}

template <typename Key, typename Info>
const DoubleLinkedRing<Key, Info>::Iterator<Key, Info>::Content<Key, Info> & DoubleLinkedRing<Key, Info>::Iterator::operator*() const
{
	const Content output;
	output.key = current->key;
	output.info = current->info;
	return output;
}

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info>::Iterator<Key, Info>::Content<Key, Info> * DoubleLinkedRing<Key, Info>::Iterator::operator->()
{
	Content *output = new Content;
	output->key = current->key;
	output->info = current->info;
	return output;
}

template <typename Key, typename Info>
const DoubleLinkedRing<Key, Info>::Iterator<Key, Info>::Content<Key, Info> * DoubleLinkedRing<Key, Info>::Iterator::operator->() const
{
	const Content *output = new Content;
	output->key = current->key;
	output->info = current->info;
	return output;
}
