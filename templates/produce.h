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
	auto outIte = output.any();

	auto ite1 = ring1.any();
	auto ite2 = ring2.any();

	dir1 ? ite1 + start1 : ite1 - start1;
	dir2 ? ite2 + start2 : ite2 - start2;

	for( ; num > 0; num-- )
	{
		for( int i = 0; i < step1; i++ )
		{
			dir ? output.insertAfter( *ite1.key, *ite1.info, outIte-- ) : output.insertBefore( *ite1.key, *ite1.info, outIte++ );
			dir1 ? ite1++ : ite1--;
		}

		for( int i = 0; i < step2; i++ )
		{
			dir ? output.insertAfter( *ite2.key, *ite2.info, outIte-- ) : output.insertBefore( *ite2.key, *ite2.info, outIte++ );
			dir1 ? ite2++ : ite2--;
		}
	}

	return output;
}
