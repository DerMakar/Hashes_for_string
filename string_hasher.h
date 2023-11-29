#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <algorithm>

struct HashTable {
	HashTable(size_t n) : hashes(std::vector<unsigned int>(n)), pow_x(std::vector<unsigned int>(n)) {
		pow_x[0] = 1;
	}
	HashTable(std::vector<unsigned int>&& hashes, std::vector<unsigned int> pow_x)
		: hashes(std::move(hashes))
		, pow_x(std::move(pow_x)) {

	}
	std::vector<unsigned int> hashes;
	std::vector<unsigned int> pow_x;	
};
 
HashTable StringHasher(const std::string& str) {
	size_t n = str.size() + 1;
	std::vector<unsigned int> hashes (n);
	std::vector<unsigned int> pow_x (n);
	pow_x[0] = 1;
	unsigned int p = 1'000'000'000 + 7;
	uint16_t x = 257;
	for (int i = 1; i < n; ++i) {
		hashes[i] = (uint64_t(hashes[i - 1]) * x + str[i - 1]) % p; // think about colisia catch
		pow_x[i] = (uint64_t(pow_x[i - 1]) * x)% p;
	}
	return { std::move(hashes), std::move(pow_x) };
}

bool EqualSubstrings(const HashTable& hash_table, unsigned int from1, unsigned int from2, unsigned int length) {
	unsigned int p = 1'000'000'000 + 7;
	return (hash_table.hashes[from1 + length - 1] + uint64_t(hash_table.hashes[from2 - 1]) * hash_table.pow_x[length]) % p ==
		(hash_table.hashes[from2 + length - 1] + uint64_t(hash_table.hashes[from1 - 1]) * hash_table.pow_x[length]) % p;
}

bool EqualSubstrings(const std::vector<unsigned int>& hashes1
	, const std::vector<unsigned int>& hashes2
	, const std::vector<unsigned int>& pow_x
	, unsigned int from1
	, unsigned int from2
	, unsigned int length) {
	unsigned int p = 1'000'000'000 + 7;
	return (hashes1[from1 + length - 1] + uint64_t(hashes2[from2 - 1]) * pow_x[length]) % p ==
		(hashes2[from2 + length - 1] + uint64_t(hashes1[from1 - 1]) * pow_x[length]) % p;
}

int CirclePartLenghth(const HashTable& hash_table) {
	size_t suf = 2;
	size_t length = hash_table.hashes.size() - 2;
	if (length == -1) return 0;
	int ans = 0;
	while (length > 0) {
		if (EqualSubstrings(hash_table, 1, suf, length)) ans = suf - 1;
		if (ans > 0) return ans;
		++suf;
		--length;
	}
	return suf - 1;
}

std::string HasCircleSubstr(const std::string& str) {
	HashTable hash_table = StringHasher(str);
	int circle_part = CirclePartLenghth(hash_table);
	std::string circle_substr = str.substr(0, circle_part);
	return circle_substr;
}

std::vector<size_t> ZFunction(const std::string& str) {
	std::vector<size_t> ans(str.size());
	HashTable hash_table = StringHasher(str);
	size_t z = 2;	
 	while (z <= ans.size()) {
		size_t length = 0;
		size_t left = z;
		size_t right = ans.size();
		while (left < right) {
			length = ((left + right) / 2) - (z - 1);
			EqualSubstrings(hash_table, 1, z, length + 1) ?	left = z + length :	right = z + length - 1;
		}
		EqualSubstrings(hash_table, 1, z, left - z + 1) ? ans[z - 1] = left - z + 1 : ans[z - 1] = 0;
		z++;
	}
	return ans;
}

std::vector<size_t> MirrorZFunc(const std::string& str) {
	size_t n = str.size();
	std::vector<unsigned int> hashes(n + 1);
	std::vector<unsigned int> rev_hashes(n + 1);
	std::vector<unsigned int> pow_x(n + 1);
	pow_x[0] = 1;
	unsigned int p = 1'000'000'000 + 7;
	uint16_t x = 257;
	for (size_t i = 1; i < n + 1; ++i) {
		hashes[i] = (uint64_t(hashes[i - 1]) * x + str[i - 1]) % p;
		pow_x[i] = (uint64_t(pow_x[i - 1]) * x) % p;
		rev_hashes[i] = (uint64_t(rev_hashes[i - 1]) * x + str[n - i]) % p;
	}
	std::vector<size_t> ans(str.size());
	size_t i = 1;
	while (i <= str.size()) {
		size_t length = 0;
		size_t left = i;
		size_t right = ans.size();
		while (left < right) {
			length = ((left + right) / 2) - (i - 1);
			EqualSubstrings(hashes, rev_hashes, pow_x, 1, i, length + 1) ? left = i + length : right = i + length - 1;
		}
		EqualSubstrings(hashes, rev_hashes, pow_x, 1, i, left - i + 1) ? ans[i - 1] = left - i + 1 : ans[i - 1] = 0;
		i++;
	}
	std::reverse(ans.begin(), ans.end());
	return ans;
}

/*
MirrorFunc returns all variants of possible palindroms counting unvisible part of data
example:
we have part data 5 4 4 5 3
MirrorFunc return variants:
5 elemets-length palidrom: 3 5 4 4 5 | 5 4 4 5 3
3 elemets-length: 3 5 4 | 4 5 3
*/
std::vector<int> MirrorFunc(const std::vector<int>& numbers) {
	unsigned int p = 1'000'000'000 + 7;
	uint16_t x = 257;
	size_t v = 1 + numbers.size() / 2;
	std::vector<int> res;
	res.reserve(v);
	res.push_back(numbers.size());
	size_t n = numbers.size() + 1;
	std::vector<unsigned int> hashes (n);
	std::vector<unsigned int> rev_hashes(n);
	std::vector<unsigned int> pow_x(n);
	pow_x[0] = 1;
	for (int i = 1; i < n; ++i) {
		hashes[i] = (uint64_t(hashes[i - 1]) * x + numbers[i - 1]) % p; // ïîäìàòü íàä ëîâëåé êîëëèçèé
		pow_x[i] = (uint64_t(pow_x[i - 1]) * x) % p;
		rev_hashes[i] = (uint64_t(rev_hashes[i - 1]) * x + numbers[n - i - 1]) % p;
	}
	size_t half = (numbers.size() / 2) + 1;
	for (size_t i = 2; i <= half; ++i) {
		size_t from1 = 1;
		size_t length = i - 1;
		size_t from2 = n - 2*i + 2;		
		if (EqualSubstrings(hashes, rev_hashes, pow_x, from1, from2, length)) {
			res.push_back(n - i);
		}
	}
	return res;
}

bool IsPalindrom(const std::vector<unsigned int>& hashes
	, const std::vector<unsigned int>& rev_hashes
	, const std::vector<unsigned int>& pow_x
	, unsigned int left
	, unsigned int right) {
	size_t n = hashes.size();
	size_t from1 = left + 1;
	size_t from2 = n - (right + 1);
	size_t length = right - left + 1;
	return EqualSubstrings(hashes, rev_hashes, pow_x, from1, from2, length);
}

std::vector<unsigned int> oddCountPolydroms(const std::vector<unsigned int>& hashes
	, const std::vector<unsigned int>& rev_hashes
	, const std::vector<unsigned int>& pow_x) {
	size_t n = hashes.size();
	std::vector<unsigned int> oddCount(n);
	for (size_t i = 1; i < n; ++i) {
		size_t left = 1;
		size_t right = std::min(i, n - i);
		while (left <= right) {
			size_t middle = (left + right) / 2;
			if (IsPalindrom(hashes, rev_hashes, pow_x, i - middle, i + middle - 2)) {
				oddCount[i] = middle;
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		oddCount[0] += oddCount[i];
	}
	return oddCount;
}

std::vector<unsigned int> evenCountPolydroms(const std::vector<unsigned int>& hashes
	, const std::vector<unsigned int>& rev_hashes
	, const std::vector<unsigned int>& pow_x) {
	size_t n = hashes.size();
	std::vector<unsigned int> evenCount(n);
	for (size_t i = 1; i < n; ++i) {
		size_t left = 1;
		size_t right = std::min(i - 1, n - i);
		while (left <= right) {
			size_t middle = (left + right) / 2;
			if (IsPalindrom(hashes, rev_hashes, pow_x, i - middle - 1, i + middle - 2)) {
				evenCount[i] = middle;
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}
		evenCount[0] += evenCount[i];
	}
	return evenCount;
}

int PolySubs(const std::string& str) {
	size_t n = str.size();
	std::vector<unsigned int> hashes (n + 1);
	std::vector<unsigned int> rev_hashes(n + 1);
	std::vector<unsigned int> pow_x(n + 1);
	pow_x[0] = 1;
	unsigned int p = 1'000'000'000 + 7;
	uint16_t x = 257;
	for (size_t i = 1; i < n + 1; ++i) {
		hashes[i] = (uint64_t(hashes[i - 1]) * x + str[i - 1]) % p;
		pow_x[i] = (uint64_t(pow_x[i - 1]) * x) % p;
		rev_hashes[i] = (uint64_t(rev_hashes[i - 1]) * x + str[n - i]) % p;
	}
	std::vector<unsigned int> oddCount = oddCountPolydroms(hashes, rev_hashes, pow_x);
	std::vector<unsigned int> evenCount = evenCountPolydroms(hashes, rev_hashes, pow_x);
	int ans = oddCount[0] + evenCount[0];
	return ans;
}
