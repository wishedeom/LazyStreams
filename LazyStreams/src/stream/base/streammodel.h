#pragma once

#include <memory>

template <typename T>
class Model
{
public:
	virtual ~Model() = 0;

	virtual bool HasNext() const = 0;
	virtual T Next() = 0;

	virtual std::unique_ptr<Model<T>> Clone() const = 0;
	virtual std::unique_ptr<Model<T>> Steal() = 0;
};

template <typename T>
inline Model<T>::~Model() = default;
