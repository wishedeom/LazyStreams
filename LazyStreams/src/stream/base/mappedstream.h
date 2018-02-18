#pragma once

#include "transformedstream.h"

#include <functional>

template <typename T>
class MappedStream final
	: public TransformedStream<T>
{
public:
	MappedStream(Stream<T> rawStream, std::function<T(T)> mapping);

	bool HasNext() const;
	T Next();

private:
	std::function<T(T)> m_mapping;
};

template <typename T>
inline MappedStream<T>::MappedStream(Stream<T> rawStream, std::function<T(T)> mapping)
	: TransformedStream(std::move(rawStream))
	, m_mapping(move(mapping))
{}

template <typename T>
inline bool MappedStream<T>::HasNext() const
{
	return RawStream().HasNext();
}

template <typename T>
inline T MappedStream<T>::Next()
{
	return m_mapping(RawStream().Next());
}
