#pragma once

#include "DoubleLinkedRing.h"

template <typename Key, typename Info>
DoubleLinkedRing<Key, Info> produce( const DoubleLinkedRing<Key, Info> &ring1,
									 int start1, int step1, bool dir1,
									 const DoubleLinkedRing<Key, Info> &ring2,
									 int start2, int step2, bool dir2,
									 int num, bool dir )
{
	DoubleLinkedRing<Key, Info> output;
	if( num < 1 || step1 < 0 || step2 < 0 )
		return output;

	output.push( Key(), Info() );
	auto outIte = output.begin();

	auto ite1 = ring1.begin();
	auto ite2 = ring2.begin();

	ite1 = dir1 ? ite1 + start1 : ite1 - start1;
	ite2 = dir2 ? ite2 + start2 : ite2 - start2;

	for( ; num > 0; num-- )
	{
		for( int i = 0; i < step1; i++ )
		{
			auto temp = *ite1;
			dir ? output.insertAfter( temp.key, temp.info, outIte ) : output.insertBefore( temp.key, temp.info, outIte );
			dir ? outIte++ : outIte--;
			dir1 ? ite1++ : ite1--;
		}

		for( int i = 0; i < step2; i++ )
		{
			auto temp = *ite2;
			dir ? output.insertAfter( temp.key,temp.info, outIte ) : output.insertBefore( temp.key, temp.info, outIte );
			dir ? outIte++ : outIte--;
			dir2 ? ite2++ : ite2--;
		}
	}

	
	outIte = output.begin();
	output.remove( outIte );
	return output;
}
