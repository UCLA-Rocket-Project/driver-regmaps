#pragma once

#pragma once
#include <utility>

// varidic max, min, and minmax implementation (named maximum, minimum and min_max to avoid confusion)
// no support for custom comparators (mainly because i'm not sure how they should be specified)

namespace detail {

	// max base case
	template <class T>
	constexpr T const &do_max(T const &v) {
		return v;
	}

	// max inductive case
	template <class T, class... Rest> // requires SameType<T, Rest...>
	constexpr T const &do_max(T const &v0, T const &v1, Rest const &... rest) {
		return do_max(v0 < v1 ? v1 : v0, rest...);
	}

	// min base case
	template <class T>
	constexpr T const &do_min(T const &v) {
		return v;
	}

	// min variadic inductive case
	template <class T, class... Rest> // requires SameType<T, Rest...>
	constexpr T const &do_min(T const &v0, T const &v1, Rest const &...rest) {
		return do_min(v0 < v1 ? v0 : v1, rest...);
	}

	// min_max base case
	template <class T>
	constexpr std::pair<T const&, T const&>
	do_min_max(T const &cmin, T const &cmax) {
		return { cmin, cmax };
	}

	// min_max inductive case
	template <class T, class... Rest> // requires SameType<T, Rest...>
	constexpr std::pair<T const &, T const &>
	do_min_max(T const &cmin, T const &cmax, T const &next, Rest const &... rest) {
		return do_min_max(
			cmin < next ? cmin : next,
			next < cmax ? cmax : next,
			rest...
		);
	}

} // namespace detail

// public interface for minimum
template <class T, class ...Rest> // requires SameType<T, Rest...>
inline constexpr T const &
minimum(T const &first, Rest const &... rest) {
	return detail::do_min(first, rest...);
}

// public interface for maximum
template <class T, class ...Rest> // requires SameType<T, Rest...>
inline constexpr T const &
maximum(T const &first, Rest const &... rest) {
	return detail::do_max(first, rest...);
}

// public interface for min_max
template <class T, class ...Rest> // requires SameType<T, Rest...>
inline constexpr std::pair<T const &, T const &>
min_max(T const &first, Rest const &... rest) {
	return detail::do_min_max(first, first, rest...);
}