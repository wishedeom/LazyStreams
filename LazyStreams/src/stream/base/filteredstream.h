#pragma once

#include "transformedstream.h"

#include <functional>

template <typename T>
class FilteredStream final
	: public TransformedStream<T>
{
public:
	FilteredStream(Stream<T> rawStream, std::function<bool(T)> predicate);

	bool HasNext() const;
	T Next();

private:
	std::function<bool(T)> m_predicate;
};

template <typename T>
inline FilteredStream<T>::FilteredStream(Stream<T> rawStream, std::function<bool(T)> predicate)
	: TransformedStream(std::move(rawStream))
	, m_predicate(move(predicate))
{}

template <typename T>
inline bool FilteredStream<T>::HasNext() const
{
	return RawStream().HasNext();
}

template <typename T>
inline T FilteredStream<T>::Next()
{
	T value;
	do
	{
		value = RawStream().Next();
	}
	while (!m_predicate(value));
	return value;
}

