#include "base/stream.h"
#include "util.h"
#include "IntegralStream.h"

Stream<int> NaturalNumbers()
{
	return IncreasingIntegralStream<int, 1>();
}
