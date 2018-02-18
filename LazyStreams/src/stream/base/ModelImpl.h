#pragma once

#include <memory>

#include "streammodel.h"

template <typename T, typename StreamType>
class ModelImpl final
	: public Model<T>
{
public:
	ModelImpl(StreamType stream);
	virtual ~ModelImpl() = default;

	virtual bool HasNext() const override;
	virtual T Next() override;

	virtual std::unique_ptr<Model<T>> Clone() const override;
	virtual std::unique_ptr<Model<T>> Steal() override;

private:
	StreamType m_stream;
};

template <typename T, typename StreamType>
inline ModelImpl<T, StreamType>::ModelImpl(StreamType stream)
	: m_stream(std::move(stream))
{}

template <typename T, typename StreamType>
inline bool ModelImpl<T, StreamType>::HasNext() const
{
	return m_stream.HasNext();
}

template <typename T, typename StreamType>
inline T ModelImpl<T, StreamType>::Next()
{
	return m_stream.Next();
}

template <typename T, typename StreamType>
inline std::unique_ptr<Model<T>> ModelImpl<T, StreamType>::Clone() const
{
	return std::make_unique<ModelImpl<T, StreamType>>(m_stream);
}

template <typename T, typename StreamType>
inline std::unique_ptr<Model<T>> ModelImpl<T, StreamType>::Steal()
{
	return std::make_unique<ModelImpl<T, StreamType>>(std::move(m_stream));
}
