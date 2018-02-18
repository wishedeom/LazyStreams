#pragma once

#include <optional>

template <typename T>
class Stream;

class StreamEndIterator final {};

template <typename T>
class StreamIterator
{
public:
	explicit StreamIterator(Stream<T>& stream);

	bool operator==(const StreamIterator& rhs) const;
	bool operator==(const StreamEndIterator& rhs) const;

	template <typename U>
	bool operator!=(const U& rhs) const;

	StreamIterator<T>& operator++();
	T operator*() const;

private:
	Stream<T>& m_stream;
	T m_value;
};

#include "stream.h"

template <typename T>
inline StreamIterator<T>::StreamIterator(Stream<T>& stream)
	: m_stream(stream)
	, m_value(stream.Next())
{}

template <typename T>
inline bool StreamIterator<T>::operator==(const StreamIterator& rhs) const
{
	return false;
}

template <typename T>
inline bool StreamIterator<T>::operator==(const StreamEndIterator& rhs) const
{
	return !m_stream.HasNext();
}

template <typename T>
template <typename U>
inline bool StreamIterator<T>::operator!=(const U& rhs) const
{
	return !(*this == rhs);
}

template <typename T>
inline StreamIterator<T>& StreamIterator<T>::operator++()
{
	m_value = m_stream.Next();
	return *this;
}

template <typename T>
inline T StreamIterator<T>::operator*() const
{
	return m_value;
}
