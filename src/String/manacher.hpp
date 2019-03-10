#pragma once

#include <string>
#include <vector>
#include <cassert>

// Finds palindromes in linear time.
// Pretreatment : O(N)
// (*) In this algorithm, inserting '$'s.('$' == 92)
template <typename T>
class Palindrome
{
	const int size_;
	std::vector<int> manacher_data_;

	std::vector<T> insert_doll(const auto &str)
	{
		const int str_size = str.size();
		if (str_size <= 1)
		{
			return str;
		}
		std::vector<T> res;
		res.push_back(str[0]);
		for (int i = 1; i < str_size; i++)
		{
			res.push_back('$');
			res.push_back(str[i]);
		}
		return res;
	}

	std::vector<int> manacher(const auto &str)
	{
		const int str_size = str.size();
		std::vector<int> res(str_size + 1);
		for (int i = 0, j = 0; i < str_size;)
		{
			while (i - j >= 0 && i + j < str_size && str[i - j] == str[i + j])
				j++;
			res[i] = j;
			int k = 1;
			while (i - k >= 0 && i + k < str_size && k + res[i - k] < j)
			{
				res[i + k] = res[i - k];
				k++;
			}
			i += k;
			j -= k;
		}
		return res;
	}

  public:
	Palindrome(const std::vector<T> &str) : size_(str.size()), manacher_data_(manacher(insert_doll(str))) {}

	// Gets whether S[i, j) is a palindrome.
	// O(1)
	bool is(int i, int j)
	{
		assert(0 <= i && i < j && j <= size_);
		return manacher_data_[i + j - 1] >= j - i;
	}
};