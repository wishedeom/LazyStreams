#pragma once

#include "base/streammodel.h"

#include <type_traits>

template <typename T>
using SuccessorFunction = T (T);

template <typename T, typename StreamPolicy>
class IntegralStream
{
	static_assert(std::is_integral_v<T>);

public:
	IntegralStream(T initial = T());

	bool HasNext() const;
	T Next();

private:
	T m_current;
};

template <typename T, typename StreamPolicy>
inline IntegralStream<T, StreamPolicy>::IntegralStream(const T initial /*= T()*/)
	: m_current(initial)
{}

template <typename T, typename StreamPolicy>
inline bool IntegralStream<T, StreamPolicy>::HasNext() const
{
	return StreamPolicy::HasNext(m_current);
}

template <typename T, typename StreamPolicy>
inline T IntegralStream<T, StreamPolicy>::Next()
{
	return StreamPolicy::Next(m_current);
}

template <typename T>
struct ConstantStreamPolicy final
{
	static bool HasNext(T x)
	{
		return true;
	}

	static T Next(T& x)
	{
		return x;
	}
};

template <typename T, T stride>
struct IncreasingStreamPolicy final
{
	static_assert(stride > 0);

	static bool HasNext(T x)
	{
		return x < std::numeric_limits<T>::max() - stride;
	}

	static T Next(T& x)
	{
		const auto prev = x;
		x += stride;
		return prev;
	}
};

template <typename T, T stride>
struct DecreasingStreamPolicy final
{
	static_assert(stride > 0);

	static bool HasNext(T x)
	{
		return x > std::numeric_limits<T>::min() + stride;
	}

	static T& Next(T& x)
	{
		const auto prev = x;
		x -= stride;
		return prev;
	}
};

template <typename T>
using ConstantIntegralStream = IntegralStream<T, ConstantStreamPolicy<T>>;

template <typename T, T stride>
using IncreasingIntegralStream = IntegralStream<T, IncreasingStreamPolicy<T, stride>>;

template <typename T, T stride>
using DecreasingIntegralStream = IntegralStream<T, DecreasingStreamPolicy<T, stride>>;
