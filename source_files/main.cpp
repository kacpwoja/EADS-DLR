#include "../templates/DoubleLinkedRing.h"
#include "../templates/produce.h"

#include <iostream>
#include <string>

using namespace std;

void wait()
{
	string in;
	cout << "Input any string to continue." << endl;
	cin >> in;
}

int main()
{
	cout << "Constructing two lists" << endl;
	DoubleLinkedRing<int, int> ring1;
	DoubleLinkedRing<int, int> ring2;

	cout << "Testing push" << endl;
	for( int i = 0; i < 10; i++ )
		ring1.push( i, i );

	cout << "Ring 1:" << endl;
	ring1.print();
	cout << "Ring 2:" << endl;
	cout << ring2 << endl;

	cout << "Ring1 size: " << ring1.size() << " Ring2 size: " << ring2.size() << endl;
	cout << "Ring1 empty: " << ring1.isEmpty() << " Ring2 empty: " << ring2.isEmpty() << endl;

	wait();

	cout << "Testing copy constructor and operator= :" << endl;
	DoubleLinkedRing<int, int> ring3( ring1 );
	ring2 = ring1;

	cout << "Ring 2:" << endl;
	ring2.print();
	cout << "Ring 3:" << endl;
	ring3.print();
	
	cout << "Testing operator == and !=:" << endl;
	bool is = ring2 == ring3;
	bool isnot = ring2 != ring3;
	cout << "2==3: " << is << " 2!=3: " << isnot << endl;
	
	cout << "Testing clear: " << endl;
	ring3.clear();
	cout << "Ring 3:" << endl;
	ring3.print();
	
	cout << "Testing search: " << endl;
	cout << "Search for 3: " << ring1.search( 3 ) << " Search for 20: " << ring1.search( 20 ) << endl;

	wait();

	cout << "Testing iterator: " << endl;
	DoubleLinkedRing<int, int>::Iterator ite1;
	ite1 = ring1.begin();
	auto ite2 = ring1.find( 3 );
	DoubleLinkedRing<int, int>::ConstIterator ite3( ite2 );

	is = ite3 == ite2;
	isnot = ite3 != ite2;
	cout << "Ite3 == Ite2: " << is << " Ite3 != Ite2: " << isnot << endl;

	ite1 = ite2;

	cout << "Testing gets: " << endl;
	cout << "Info: " << ite1.getInfo() << " Key: " << ite1.getKey() << endl;

	cout << "Testing operator*" << endl;
	DoubleLinkedRing<int, int>::Iterator::Content out = *ite1;
	cout << "Info: " << out.info << " Key: " << out.key << endl;

	//cout << "Testing operator->" << endl;
	//cout << "Info: " << ite1->info << " Key: " << ite1->key << endl;

	cout << "Changing to 12 " << endl;
	out.info = 12; out.key = 12;

	ring1.print();

	wait();

	cout << "Testing ++ and adding" << endl;

	ite1++;
	ring1.insertAfter( 13, 13, ite1 );
	ring1.insertBefore( 13, 13, ite1 );

	ring1.print();

	cout << "Testing remove: " << endl;
	ring1.remove( ite1 );

	ring1.print();

	wait();

	cout << "BIG TEST: PRODUCE" << endl;
	DoubleLinkedRing<int, int> pro1, pro2;
	for( int i = 1; i < 5; i++ )
		pro1.push( i, i );
	for( int i = 1; i < 4; i++ )
		pro2.push( i * 10, i * 10 );
	cout << "FIRST RING:" << endl;
	pro1.print();
	cout << "SECOND RING:" << endl;
	pro2.print();

	DoubleLinkedRing<int, int> result;
	result = produce( pro1, 2, 3, true, pro2, 1, 2, false, 3, true );
	cout << "PRODUCED RING:" << endl;
	result.print();

	wait();
	return 0;
}