
#pragma once
#include <utility>

// varidic max, min, and minmax implementation (named maximum, minimum and min_max to avoid confusion)
// no support for custom comparators (mainly because i'm not sure how they should be specified)

namespace regmap {
	/**
	 * Modified from: https://gist.github.com/thomcc/7739146
	 */
	namespace minmax {
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
	}
	/**
	 * Modified from: https://stackoverflow.com/questions/30346652/enforce-variadic-template-of-certain-type
	 */
	namespace types_all_same {
		template<bool...> struct bool_pack;
		template<bool... bs>
		//if any are false, they'll be shifted in the second version, so types won't match
		using all_true_internal = std::is_same<bool_pack<bs..., true>, bool_pack<true, bs...>>;
		template <typename... Ts>
		using all_true = all_true_internal<Ts::value...>;
	}
	/*
	 * Public interfaces
	 */
	template <typename T, typename... Ts>
	using all_same = types_all_same::all_true<std::is_same<T,Ts>...>;

	template <class T, class ...Rest> // requires SameType<T, Rest...>
	inline constexpr T const &
	minimum(T const &first, Rest const &... rest) {
		return minmax::do_min(first, rest...);
	}
	template <class T, class ...Rest> // requires SameType<T, Rest...>
	inline constexpr T const &
	maximum(T const &first, Rest const &... rest) {
		return minmax::do_max(first, rest...);
	}
}