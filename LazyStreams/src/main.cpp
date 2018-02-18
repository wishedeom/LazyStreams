#include "stream/IntegralStream.h"
#include "stream/base/stream.h"
#include "stream/base/finitestream.h"
#include "stream/util.h"

#include <iostream>

int main()
{
	//Stream<int> s = NaturalNumbers().Map(Square<int>).Filter(IsEven<int>).Take(10);
	//while (s.HasNext())
	//{
	//	std::cout << s.Next() << '\n';
	//}

	for (const auto x : NaturalNumbers().Map(Square<int>).Filter(IsEven<int>)/*.Take(10)*/)
	{
		std::cout << x << '\n';
	}
}
