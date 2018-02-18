#pragma once

#include "stream.h"

template <typename T>
class TransformedStream
{
public:
	TransformedStream(Stream<T> rawStream);

protected:
	const Stream<T>& RawStream() const;
	Stream<T>& RawStream();

private:
	Stream<T> m_rawStream;
};

template <typename T>
inline TransformedStream<T>::TransformedStream(Stream<T> rawStream)
	: m_rawStream(std::move(rawStream))
{}

template <typename T>
inline const Stream<T>& TransformedStream<T>::RawStream() const
{
	return m_rawStream;
}

template <typename T>
inline Stream<T>& TransformedStream<T>::RawStream()
{
	return m_rawStream;
}
