#pragma once

template <typename T>
class Stream;

Stream<int> NaturalNumbers();

template <typename T = int>
T Square(T x)
{
	return x * x;
}

template <typename T = int>
bool IsEven(T x)
{
	return x % 2 == 0;
}
