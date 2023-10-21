#pragma once

#include "Exception.h"
#include "Data.h"

// 1.1
void createData1(const std::string& path = "file.txt", const char& separator = '\n') {
	std::ofstream file(path, std::ios::out | std::ios::trunc);
	if (!file) throw Exception("Unable to create file at specified path: " + path);

	std::random_device dev;
	std::mt19937 rng(dev());
	uniform_distribution_type dist(range_start, range_end);

	for (size_t i = 0; i <= number_amount; ++i) file << dist(rng) << separator;
	file.close();
}

// 1.2
void createData2(const std::string& path = "file.txt", const char& separator = '\n') {
	std::ofstream file(path, std::ios::out | std::ios::trunc);
	if (!file) throw Exception("Unable to create file at specified path: " + path);

	std::random_device dev;
	std::mt19937 rng(dev());
	uniform_distribution_type dist(range_start, range_end);

	std::array<value_type, number_amount> temp_arr{};
	std::ranges::generate(temp_arr, [&] {return dist(rng);});
	std::ranges::copy(temp_arr, std::ostream_iterator<value_type>(file, &separator));
	file.close();
}

// 2.1 
template <class _Cont>
	requires containerConcept<_Cont>
void loadData1(std::ifstream& file, _Cont& cont) {
	if (!file) throw Exception("unable to open file");

	value_type line;
	while (file >> line) cont.push_back(line); 
}

// 2.2
template <class _Cont>
	requires containerConcept<_Cont>
void loadData2(std::ifstream& file, _Cont& cont) {
	if (!file) throw Exception("unable to open file");

	std::ranges::copy(std::istream_iterator<value_type>(file), 
		              std::istream_iterator<value_type>(), 
		              std::back_inserter(cont));
}

// 3

template <class _Iter>
	requires iterConcept<_Iter>
void func1(_Iter begin, _Iter end) {
	value_type maxim = *std::max_element(begin, end);
	auto temp = begin;
	std::advance(temp, std::distance(begin, end)-1);
	value_type last = *temp;
	value_type sqrt = std::sqrt(std::abs(maxim * last));
	std::for_each(begin, end, [&sqrt](value_type& el) {el += sqrt;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func2(_Iter begin, _Iter end) {
	auto check = std::find_if(begin, end, [](const auto& el) {return el < 0;});
	if (check == end) throw Exception("no negative elements");

	value_type first_neg = *check;
	auto temp = begin;
	if (std::distance(begin, end) < 50) throw Exception("less than 50 elements");

	std::advance(temp, 50 - 1);
	value_type last = *temp;
	value_type res = first_neg + last;
	std::for_each(begin, end, [&res](value_type& el) {el /= res;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func3(_Iter begin, _Iter end) {
	value_type maxim = *std::max_element(begin, end);
	std::for_each(begin, end, [&maxim](value_type& el) {el -= maxim;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func4(_Iter begin, _Iter end) {
	value_type minim = *std::min_element(begin, end);
	std::for_each(begin, end, [&minim](value_type& el) {el *= minim;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func5(_Iter begin, _Iter end) {
	value_type res = std::reduce(begin, end) / 
		             std::distance(begin, end);
	std::for_each(begin, 
		          end, 
		          [&res](value_type& el) {
			             el = static_cast<int>(std::abs(el)) % 2 != 0 ? // can't mod a float
						 el / res : 
		                 el / 1;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func6(_Iter begin, _Iter end) {
	value_type sumy = std::reduce(begin, end);
	std::for_each(begin, end, [&sumy](value_type& el) {el -= sumy;});
};

template<class _Iter>
	requires iterConcept<_Iter>
std::reverse_iterator<_Iter> reversed(_Iter it) { 
	return std::reverse_iterator<_Iter>(std::forward<_Iter>(it)); }

template <class _Iter>
	requires iterConcept<_Iter>
void func7(_Iter begin, _Iter end) {
	auto check = std::find_if(begin, end, [](const auto& el) {return el < 0;});
	if (check == end) throw Exception("no negative elements");

	value_type first_neg = *check;
	value_type last_neg = *std::find_if(reversed(end), 
		                                reversed(begin), 
		                                [](const auto& el) {return el < 0;});
	value_type res = 2 * (first_neg + last_neg);
	size_t count = 1;

	for (auto it = begin; it != end; ++it) {
		if (count % 3 == 0) *it *= res;
		count++;
	}
};

template <class _Iter>
	requires iterConcept<_Iter>
void func8(_Iter begin, _Iter end) {
	auto check = std::find_if(begin, 
		                      end, 
		                      [](const value_type& el) {
			return static_cast<int>(std::abs(el)) % 2 != 0;}); // can't mod a float
	if (check == end) throw Exception("no odd elements");

	value_type first_odd = *check;
	std::for_each(begin, end, [&first_odd](auto& el) {el += first_odd;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func9(_Iter begin, _Iter end) {
	auto check = std::find_if(begin, 
		                      end, 
		                      [](const auto& el) {return el < 0;});
	if (check == end) throw Exception("no elements < 0");

	value_type first_neg = *check;
	std::for_each(begin,  
		          end, 
		          [&first_neg](value_type& el) {
			                   el = static_cast<int>(std::abs(el)) % 2 == 0 ? // can't mod a float
			                   el * first_neg : 
		                       el * 1;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func10(_Iter begin, _Iter end) {
	auto check = std::find_if(reversed(end), 
		                      reversed(begin), 
		                      [](const value_type& el) {return el < 0;});
	if (check == reversed(begin)) throw Exception("no negative elements"); 

	value_type last_neg_half = (*check) / 2;
	std::for_each(begin, end, [&last_neg_half](value_type& el) {el += last_neg_half;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func11(_Iter begin, _Iter end) {
	value_type maxim = *std::max_element(begin, end);

	std::for_each(begin, end, [&maxim](value_type& el) {el /= maxim;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func12(_Iter begin, _Iter end) {
	value_type res = std::reduce(begin, end) / std::distance(begin, end);

	std::for_each(begin, end, [&res](value_type& el) {el = el == 0 ? res : el;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func13(_Iter begin, _Iter end) {
	value_type res = std::sqrt(std::abs(*std::min_element(begin, end)));

	std::for_each(begin, end, [&res](value_type& el) {el = el >= 0 ? res : el;});
};

#pragma warning( push )
#pragma warning( disable : 4244)

bool meets_criteria(auto& el) { return el < 0; };

int my_conditional_binary_op(int a, int b) { return meets_criteria(b) ? a + b : a; }

template <class _Iter>
	requires iterConcept<_Iter>
void func14(_Iter begin, _Iter end) {
	value_type half_neg_sumy = std::accumulate(begin, end, 0, my_conditional_binary_op)/2;

	std::for_each(begin, end, [&half_neg_sumy](value_type& el) {el += half_neg_sumy;});
};

#pragma warning( pop ) 

template <class _Iter>
	requires iterConcept<_Iter>
void func15(_Iter begin, _Iter end) {
	auto maxim_abs = -std::numeric_limits<double>::infinity();
	auto minim_abs = std::numeric_limits<double>::infinity();
	
	for (auto it = begin; it != end; it++) {
		if (std::abs(*it) > maxim_abs) maxim_abs = std::abs(*it);
		if (std::abs(*it) < minim_abs) minim_abs = std::abs(*it);
	}

	value_type res = (static_cast<value_type>(maxim_abs) + 
		              static_cast<value_type>(minim_abs)) / 2;

	std::for_each(begin, end, [&res](value_type& el) {el += res;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func16(_Iter begin, _Iter end) {
	value_type maxim = *std::max_element(begin, end);
	value_type minim = *std::min_element(begin, end);

	std::for_each(begin, end, [&maxim, &minim](value_type& el) {el = el / minim + maxim;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func17(_Iter begin, _Iter end) {
	value_type maxim = *std::max_element(begin, end);

	std::for_each(begin, end, [&maxim](value_type& el) {el = el >= 0 ? maxim : el;});
};

template <class _Iter>
	requires iterConcept<_Iter>
void func18(_Iter begin, _Iter end) {
	value_type diff = (*std::max_element(begin, end)) - 
		              (*std::min_element(begin, end));

	std::for_each(begin, end, [&diff](value_type& el) {
		el = static_cast<int>(std::abs(el)) % 2 == 0 ? diff : el;}); // can't mod a float
};

template <class _Iter>
	requires iterConcept<_Iter>
void func19(_Iter begin, _Iter end) {
	value_type maxim_half = (*std::max_element(begin, end)) / 2;
	size_t count = 1;

	for (auto it = begin; it != end; it++) {
		if (*it < 0) {
			if (count % 2 == 0) *it = maxim_half;
			count++;
		}
	}
};

template <class _Iter>
	requires iterConcept<_Iter>
void func20(_Iter begin, _Iter end) {
	value_type res = std::reduce(begin, end) / std::distance(begin, end);
	size_t count = 1;

	for (auto it = begin; it != end; it++) {
		if (*it >= 0) {
			if (count % 3 == 0) *it = res;
			count++;
		}
	}
};

template <class _Iter>
	requires iterConcept<_Iter>
std::unordered_map<size_t, std::function<void(_Iter, _Iter)>> iterfuncs{
	{1, func1<_Iter>},   {2, func2<_Iter>},   {3, func3<_Iter>},   {4, func4<_Iter>},   {5, func5<_Iter>},
	{6, func6<_Iter>},   {7, func7<_Iter>},   {8, func8<_Iter>},   {9, func9<_Iter>},   {10, func10<_Iter>},
	{11, func11<_Iter>}, {12, func12<_Iter>}, {13, func13<_Iter>}, {14, func14<_Iter>}, {15, func15<_Iter>},
	{16, func16<_Iter>}, {17, func17<_Iter>}, {18, func18<_Iter>}, {19, func19<_Iter>}, {20, func20<_Iter>}
};

// 3.2 declaration
template <class _Iter>
	requires iterConcept<_Iter>
void modify2(_Iter  begin,
	         _Iter  end,
	         size_t which);

// 3.1 
template <class _Cont>
	requires containerConcept<_Cont>
void modify1(_Cont& cont, size_t which) { 
	 modify2(cont.begin(), 
		     cont.end(), 
		     which);

	value_type sumy = std::reduce(cont.begin(), cont.end());
	value_type sumy_abs{};
	for (const value_type& el : cont) sumy_abs += std::abs(el);
	value_type res = sumy_abs / cont.size();

	cont.push_back(sumy); cont.push_back(res);
}

// 3.2 
template <class _Iter>
	requires iterConcept<_Iter>
void modify2(_Iter  begin, 
	         _Iter  end, 
	         size_t which) { 
	iterfuncs<_Iter>[which](begin, end-1); }

// 3.3
template <class _Cont, class Func>
	requires containerConcept<_Cont> and funcConcept<Func>
void modify3(_Cont& cont, Func func) { 
	std::ranges::for_each(cont, func);
}

// 3.4 
template <class Func>
	requires funcConcept<Func>
void modify4(Func func, 
	         const std::string& filename1 = "file.txt", 
	         const std::string& filename2 = "res_file.txt") {
	std::ifstream initial_file(filename1);
	if (!initial_file) throw Exception("unable to open file");

	std::ofstream res_file(filename2);
	if (!res_file) throw Exception("unable to create file");

	std::ranges::transform(std::istream_iterator<value_type>(initial_file), 
		                   std::istream_iterator<value_type>(),
		                   std::ostream_iterator<std::string>(res_file), 
		                   func);
	initial_file.close();
	res_file.close();
}

// 4.1
template <class _Cont>
	requires containerConcept<_Cont>
void outputResult1(std::ofstream& file, 
	               _Cont&         cont, 
	               const char&    separator = '\n') {
	if (!file) throw Exception("unable to open file");

	std::ranges::for_each(cont, 
		                  [&](const auto& el) {
			                  file << std::to_string(el) << separator;});
}

// 4.2
template <class _Cont>
	requires containerConcept<_Cont>
void outputResult2(std::ofstream& file, 
	               _Cont&         cont, 
	               const char&    separator = '\n') {
	if (!file) throw Exception("unable to open file");

	std::ranges::copy(cont, 
		              std::ostream_iterator<value_type>(file, &separator));
}
