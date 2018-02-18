#pragma once

#include "streammodel.h"
#include "ModelImpl.h"
#include "streamiterator.h"

#include <memory>
#include <functional>

template <typename T>
class Stream final
{
public:
	template <typename StreamType>
	Stream(const StreamType& model);

	Stream(const Stream& stream);
	Stream(Stream&& stream) = default;

	bool HasNext() const;
	T Next();

	// Transformers
	Stream Take(size_t count) const;
	Stream Map(std::function<T(T)> mapping) const;
	Stream Filter(std::function<bool(T)> predicate) const;

	// Iterators
	StreamIterator<T> begin();
	StreamEndIterator end();

private:
	std::unique_ptr<Model<T>> m_model;
};

template <typename T>
template <typename StreamType>
inline Stream<T>::Stream(const StreamType& model)
	: m_model(std::make_unique<ModelImpl<T, StreamType>>(model))
{}

template <typename T>
inline Stream<T>::Stream(const Stream<T>& stream)
	: m_model(stream.m_model->Clone())
{}

template <typename T>
inline bool Stream<T>::HasNext() const
{
	return m_model->HasNext();
}

template <typename T>
inline T Stream<T>::Next()
{
	return m_model->Next();
}

#include "finitestream.h"

template <typename T>
inline Stream<T> Stream<T>::Take(const size_t count) const
{
	return FiniteStream<T>(*this, count);
}

#include "mappedstream.h"

template <typename T>
inline Stream<T> Stream<T>::Map(std::function<T(T)> mapping) const
{
	return MappedStream<T>(*this, move(mapping));
}

#include "filteredstream.h"

template <typename T>
inline Stream<T> Stream<T>::Filter(std::function<bool(T)> predicate) const
{
	return FilteredStream<T>(*this, move(predicate));
}

template <typename T>
inline StreamIterator<T> Stream<T>::begin()
{
	return StreamIterator<T>(*this);
}

template <typename T>
inline StreamEndIterator Stream<T>::end()
{
	return {};
}
