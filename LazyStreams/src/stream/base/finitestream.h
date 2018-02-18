#pragma once

#include "transformedstream.h"

template <typename T>
class FiniteStream final
	: public TransformedStream<T>
{
public:
	FiniteStream(Stream<T> rawStream, size_t elements);

	bool HasNext() const;
	T Next();

private:
	size_t m_elements;
	size_t m_count;
};

template <typename T>
inline FiniteStream<T>::FiniteStream(Stream<T> rawStream, const size_t elements)
	: TransformedStream(std::move(rawStream))
	, m_elements(elements)
	, m_count(0)
{}

template <typename T>
inline bool FiniteStream<T>::HasNext() const
{
	if (!RawStream().HasNext())
	{
		return false;
	}

	if (m_count >= m_elements)
	{
		return false;
	}

	return true;
}

template <typename T>
inline T FiniteStream<T>::Next()
{
	++m_count;
	return RawStream().Next();
}
