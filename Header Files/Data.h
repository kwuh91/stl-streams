#pragma once

#include <iostream>
#include <deque>
#include <list>
#include <random>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <string>
#include <functional>
#include <unordered_map>
#include <cmath>
#include <numeric>
#include <limits>
#include <type_traits>
#include <array>
#include <ranges>

constexpr auto range_start   = -50; // change the start of the range
constexpr auto range_end     = 50;  // change the end of the range
constexpr auto number_amount = 100; // change the amount of elements

using value_type = double;                 // change type
using cont_type = std::vector<value_type>; // change container type

// define type of distribution
template <bool is_integral, typename T> struct uniform_distribution_selector;

template <typename T> struct uniform_distribution_selector<true, T> {
	using type = typename std::uniform_int_distribution<T>;
};

template <typename T> struct uniform_distribution_selector<false, T> {
	using type = typename std::uniform_real_distribution<T>;
};

using uniform_distribution_type = typename uniform_distribution_selector<std::is_integral<value_type>::value, value_type>::type;

// concept for functors
template <class _Func>
concept funcConcept = requires(value_type _i, _Func _f) {_f(_i);};

// concpet for iterators
template <class _Iter> concept iterConcept = requires(_Iter _i) {
    std::totally_ordered<_Iter>;
    {*_i}  -> std::same_as<std::iter_reference_t<_Iter>>;
    {_i++} -> std::same_as<_Iter>;
    {_i--} -> std::same_as<_Iter>;
    {--_i} -> std::same_as<_Iter&>;
    {++_i} -> std::same_as<_Iter&>;
};

// concept for containers
template <class _Cont>
concept containerConcept = requires(_Cont a, const _Cont b)
{
    requires std::regular                <_Cont>;
    requires std::swappable              <_Cont>;
    requires std::same_as                <typename _Cont::reference,
                                          typename _Cont::value_type&>;
    requires std::same_as                <typename _Cont::const_reference,
                                          const typename _Cont::value_type&>;
    requires std::forward_iterator       <typename _Cont::iterator>;
    requires std::forward_iterator       <typename _Cont::const_iterator>;
    requires std::signed_integral        <typename _Cont::difference_type>;
    requires std::same_as                <typename _Cont::difference_type,
                                          typename std::iterator_traits<
                                          typename _Cont::iterator>::difference_type>;
    requires std::same_as                <typename _Cont::difference_type,
                                          typename std::iterator_traits
                                         <typename _Cont::const_iterator>::difference_type>;
    { a.begin() } -> std::same_as        <typename _Cont::iterator>;
    { a.end() } -> std::same_as          <typename _Cont::iterator>;
    { b.begin() } -> std::same_as        <typename _Cont::const_iterator>;
    { b.end() } -> std::same_as          <typename _Cont::const_iterator>;
    { a.cbegin() } -> std::same_as       <typename _Cont::const_iterator>;
    { a.cend() } -> std::same_as         <typename _Cont::const_iterator>;
    { a.size() } -> std::same_as         <typename _Cont::size_type>;
    { a.max_size() } -> std::same_as     <typename _Cont::size_type>;
    { a.empty() } -> std::convertible_to <bool>;
};
